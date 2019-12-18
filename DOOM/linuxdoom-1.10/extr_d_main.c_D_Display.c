#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int gamestate_t ;
typedef  int boolean ;

/* Variables and functions */
 int /*<<< orphan*/  AM_Drawer () ; 
 int /*<<< orphan*/  D_PageDrawer () ; 
 int /*<<< orphan*/  F_Drawer () ; 
#define  GS_DEMOSCREEN 131 
#define  GS_FINALE 130 
#define  GS_INTERMISSION 129 
#define  GS_LEVEL 128 
 int /*<<< orphan*/  HU_Drawer () ; 
 int /*<<< orphan*/  HU_Erase () ; 
 int /*<<< orphan*/  I_FinishUpdate () ; 
 int I_GetTime () ; 
 int /*<<< orphan*/  I_SetPalette (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_UpdateNoBlit () ; 
 int /*<<< orphan*/  M_Drawer () ; 
 int /*<<< orphan*/  NetUpdate () ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  R_DrawViewBorder () ; 
 int /*<<< orphan*/  R_ExecuteSetViewSize () ; 
 int /*<<< orphan*/  R_FillBackScreen () ; 
 int /*<<< orphan*/  R_RenderPlayerView (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCREENHEIGHT ; 
 int /*<<< orphan*/  SCREENWIDTH ; 
 int /*<<< orphan*/  ST_Drawer (int,int) ; 
 int /*<<< orphan*/  V_DrawPatchDirect (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WI_Drawer () ; 
 int /*<<< orphan*/  W_CacheLumpName (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ automapactive ; 
 size_t displayplayer ; 
 int gamestate ; 
 scalar_t__ gametic ; 
 int inhelpscreens ; 
 int menuactive ; 
 scalar_t__ nodrawers ; 
 scalar_t__ paused ; 
 int /*<<< orphan*/ * players ; 
 int scaledviewwidth ; 
 scalar_t__ setsizeneeded ; 
 int viewactive ; 
 int viewheight ; 
 scalar_t__ viewwindowx ; 
 int viewwindowy ; 
 int /*<<< orphan*/  wipe_EndScreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wipe_Melt ; 
 int wipe_ScreenWipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wipe_StartScreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wipegamestate ; 

void D_Display (void)
{
    static  boolean		viewactivestate = false;
    static  boolean		menuactivestate = false;
    static  boolean		inhelpscreensstate = false;
    static  boolean		fullscreen = false;
    static  gamestate_t		oldgamestate = -1;
    static  int			borderdrawcount;
    int				nowtime;
    int				tics;
    int				wipestart;
    int				y;
    boolean			done;
    boolean			wipe;
    boolean			redrawsbar;

    if (nodrawers)
	return;                    // for comparative timing / profiling
		
    redrawsbar = false;
    
    // change the view size if needed
    if (setsizeneeded)
    {
	R_ExecuteSetViewSize ();
	oldgamestate = -1;                      // force background redraw
	borderdrawcount = 3;
    }

    // save the current screen if about to wipe
    if (gamestate != wipegamestate)
    {
	wipe = true;
	wipe_StartScreen(0, 0, SCREENWIDTH, SCREENHEIGHT);
    }
    else
	wipe = false;

    if (gamestate == GS_LEVEL && gametic)
	HU_Erase();
    
    // do buffered drawing
    switch (gamestate)
    {
      case GS_LEVEL:
	if (!gametic)
	    break;
	if (automapactive)
	    AM_Drawer ();
	if (wipe || (viewheight != 200 && fullscreen) )
	    redrawsbar = true;
	if (inhelpscreensstate && !inhelpscreens)
	    redrawsbar = true;              // just put away the help screen
	ST_Drawer (viewheight == 200, redrawsbar );
	fullscreen = viewheight == 200;
	break;

      case GS_INTERMISSION:
	WI_Drawer ();
	break;

      case GS_FINALE:
	F_Drawer ();
	break;

      case GS_DEMOSCREEN:
	D_PageDrawer ();
	break;
    }
    
    // draw buffered stuff to screen
    I_UpdateNoBlit ();
    
    // draw the view directly
    if (gamestate == GS_LEVEL && !automapactive && gametic)
	R_RenderPlayerView (&players[displayplayer]);

    if (gamestate == GS_LEVEL && gametic)
	HU_Drawer ();
    
    // clean up border stuff
    if (gamestate != oldgamestate && gamestate != GS_LEVEL)
	I_SetPalette (W_CacheLumpName ("PLAYPAL",PU_CACHE));

    // see if the border needs to be initially drawn
    if (gamestate == GS_LEVEL && oldgamestate != GS_LEVEL)
    {
	viewactivestate = false;        // view was not active
	R_FillBackScreen ();    // draw the pattern into the back screen
    }

    // see if the border needs to be updated to the screen
    if (gamestate == GS_LEVEL && !automapactive && scaledviewwidth != 320)
    {
	if (menuactive || menuactivestate || !viewactivestate)
	    borderdrawcount = 3;
	if (borderdrawcount)
	{
	    R_DrawViewBorder ();    // erase old menu stuff
	    borderdrawcount--;
	}

    }

    menuactivestate = menuactive;
    viewactivestate = viewactive;
    inhelpscreensstate = inhelpscreens;
    oldgamestate = wipegamestate = gamestate;
    
    // draw pause pic
    if (paused)
    {
	if (automapactive)
	    y = 4;
	else
	    y = viewwindowy+4;
	V_DrawPatchDirect(viewwindowx+(scaledviewwidth-68)/2,
			  y,0,W_CacheLumpName ("M_PAUSE", PU_CACHE));
    }


    // menus go directly to the screen
    M_Drawer ();          // menu is drawn even on top of everything
    NetUpdate ();         // send out any new accumulation


    // normal update
    if (!wipe)
    {
	I_FinishUpdate ();              // page flip or blit buffer
	return;
    }
    
    // wipe update
    wipe_EndScreen(0, 0, SCREENWIDTH, SCREENHEIGHT);

    wipestart = I_GetTime () - 1;

    do
    {
	do
	{
	    nowtime = I_GetTime ();
	    tics = nowtime - wipestart;
	} while (!tics);
	wipestart = nowtime;
	done = wipe_ScreenWipe(wipe_Melt
			       , 0, 0, SCREENWIDTH, SCREENHEIGHT, tics);
	I_UpdateNoBlit ();
	M_Drawer ();                            // menu is drawn even on top of wipes
	I_FinishUpdate ();                      // page flip or blit buffer
    } while (!done);
}