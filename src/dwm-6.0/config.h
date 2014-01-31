/* See LICENSE file for copyright and license details. */

/* Patches applied:
 * - uselessgap : gaps on clients for aesthetic purposes (on)
 * - smfact : enable resizing the clients on the stack (off)
 * - movestack : enable moving clients on the stack (on)
 * - bottombar : add another status bar on the bottom (off)
 */

/* appearance */
static const char font[]            = "Termsyn.icons-7";
static const char normbordercolor[] = "#0d0d0d";
static const char normbgcolor[]     = "#0d0d0d";
static const char normfgcolor[]     = "#f2f2f2";
static const char selbordercolor[]  = "#d8d8d8";
static const char selbgcolor[]      = "#3b3b3b";
static const char selfgcolor[]      = "#d8d8d8";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 18;        /* gap pixel between windows */
static const unsigned int snap      = 1;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* minimal height of a client */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool extrabar          = False;    /* False means no extra bar */

/* tagging */
static const char *tags[] = { "½", "®", "¨", "ê", "º" };

/* tags opening and closing markers */
static const char *tagsopen = " ";
static const char *tagsclose = " ";

/* tags mask */
#define TAG_UTIL    1 << 0
#define TAG_WWW     1 << 1
#define TAG_DOC     1 << 2
#define TAG_MEDIA   1 << 3
#define TAG_ETC     1 << 4

static const Rule rules[] = {
	/* class            instance    title            tags mask    isfloating   monitor */
	{ "URxvt",          NULL,       "ranger",        TAG_UTIL,    False,       -1 },
	{ "Thunar",         NULL,       NULL,            TAG_UTIL,    False,       -1 },
	{ "Bcompare",       NULL,       NULL,            TAG_UTIL,    False,       -1 },
	{ "Leafpad",        NULL,       NULL,            TAG_UTIL,    False,       -1 },
	{ "Eclipse",        NULL,       NULL,            TAG_UTIL,    False,       -1 },
	{ "Pidgin",         NULL,       NULL,            TAG_WWW,     False,       -1 },
	{ "Firefox",        NULL,       NULL,            TAG_WWW,     False,       -1 },
	{ "Chromium",       NULL,       NULL,            TAG_WWW,     False,       -1 },
	{ "luakit",         NULL,       NULL,            TAG_WWW,     False,       -1 },
	{ "Evince",         NULL,       NULL,            TAG_DOC,     False,       -1 },
	{ "FBReader",       NULL,       NULL,            TAG_DOC,     False,       -1 },
	{ "Gimp",           NULL,       NULL,            TAG_MEDIA,   False,       -1 },
	{ "Ario",           NULL,       NULL,            TAG_MEDIA,   False,       -1 },
	{ "Darktable",      NULL,       NULL,            TAG_MEDIA,   False,       -1 },
	{ "Smplayer",       NULL,       NULL,            TAG_MEDIA,   False,       -1 },
	{ "fontforge",      NULL,       NULL,            TAG_ETC,     False,       -1 },
	{ "Lxappearance",   NULL,       NULL,            TAG_ETC,     False,       -1 },
	{ "Qpaeq",          NULL,       NULL,            TAG_ETC,     False,       -1 },
	{ "Pavucontrol",    NULL,       NULL,            TAG_ETC,     False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const float smfact     = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "þ",      tile },    /* first entry is default */
	{ "ý",      NULL },    /* no layout function means floating behavior */
	{ "ÿ",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]        = { "dmenu_run", "-b", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]         = { "urxvtc", NULL };
static const char *rangercmd[]       = { "urxvtc", "-e", "ranger", NULL };
static const char *thunarcmd[]       = { "thunar", NULL };
static const char *thunarsucmd[]     = { "gksu", "thunar", NULL };
static const char *scrotcmd[]        = { "scrot", "-q", "100", "-e", "mv\ $f\ ~/img/screenshots", NULL };
static const char *lockscreencmd[]   = { "xscreensaver-command", "--lock", NULL };
static const char *mpdplaycmd[]      = { "mpdplay", NULL };
static const char *dwmmenucmd[]      = { "dwm-menu", NULL };
static const char *audiomutevolcmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *audiodecvolcmd[]  = { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *audioincvolcmd[]  = { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *mpctogglecmd[]    = { "mpc", "toggle", NULL };
static const char *mpcstopcmd[]      = { "mpc", "stop", NULL };
static const char *mpcprevcmd[]      = { "mpc", "prev", NULL };
static const char *mpcnextcmd[]      = { "mpc", "next", NULL };

static Key keys[] = {
	/* modifier                     key          function        argument */
	{ MODKEY,                       XK_p,        spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,   spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,        spawn,          {.v = rangercmd } },
	{ MODKEY,                       XK_w,        spawn,          {.v = thunarcmd } },
	{ MODKEY|ShiftMask,             XK_w,        spawn,          {.v = thunarsucmd } },
	{ 0,                            0xff61,      spawn,          {.v = scrotcmd } },
	{ ControlMask|AltMask,          XK_l,        spawn,          {.v = lockscreencmd } },
	{ MODKEY,                       XK_o,        spawn,          {.v = mpdplaycmd } },
	{ MODKEY,                       XK_grave,    spawn,          {.v = dwmmenucmd } },
	{ 0,                            0x1008ff11,  spawn,          {.v = audiodecvolcmd } },
	{ 0,                            0x1008ff12,  spawn,          {.v = audiomutevolcmd } },
	{ 0,                            0x1008ff13,  spawn,          {.v = audioincvolcmd } },
	{ 0,                            0x1008ff14,  spawn,          {.v = mpctogglecmd } },
	{ 0,                            0x1008ff15,  spawn,          {.v = mpcstopcmd } },
	{ 0,                            0x1008ff16,  spawn,          {.v = mpcprevcmd } },
	{ 0,                            0x1008ff17,  spawn,          {.v = mpcnextcmd } },
	{ MODKEY,                       XK_b,        togglebar,      {0} },
	/* { MODKEY,                       XK_b,        toggleextrabar, {0} }, */
	{ MODKEY,                       XK_j,        focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,        focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,        movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,        movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,        incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,        incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,        setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,        setmfact,       {.f = +0.05} },
	/* { MODKEY|ShiftMask,             XK_h,        setsmfact,      {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,        setsmfact,      {.f = -0.05} }, */
	{ MODKEY,                       XK_Return,   zoom,           {0} },
	{ MODKEY,                       XK_Tab,      view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,        killclient,     {0} },
	{ MODKEY,                       XK_t,        setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,        setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,        setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,    setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,    togglefloating, {0} },
	{ MODKEY,                       XK_0,        view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,        tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,    focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,   tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                        0)
	TAGKEYS(                        XK_2,                        1)
	TAGKEYS(                        XK_3,                        2)
	TAGKEYS(                        XK_4,                        3)
	TAGKEYS(                        XK_5,                        4)
	TAGKEYS(                        XK_6,                        5)
	TAGKEYS(                        XK_7,                        6)
	TAGKEYS(                        XK_8,                        7)
	TAGKEYS(                        XK_9,                        8)
	{ MODKEY|ShiftMask,             XK_q,        quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

