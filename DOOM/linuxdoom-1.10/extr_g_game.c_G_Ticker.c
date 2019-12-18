#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ forwardmove; scalar_t__ consistancy; int buttons; } ;
typedef  TYPE_2__ ticcmd_t ;
struct TYPE_9__ {scalar_t__ playerstate; char* message; TYPE_2__ cmd; TYPE_1__* mo; } ;
struct TYPE_7__ {scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_Ticker () ; 
 int BACKUPTICS ; 
#define  BTS_PAUSE 143 
#define  BTS_SAVEGAME 142 
 int BTS_SAVEMASK ; 
 int BTS_SAVESHIFT ; 
 int BT_SPECIAL ; 
 int BT_SPECIALMASK ; 
 int /*<<< orphan*/  D_PageTicker () ; 
 int /*<<< orphan*/  F_StartFinale () ; 
 int /*<<< orphan*/  F_Ticker () ; 
#define  GS_DEMOSCREEN 141 
#define  GS_FINALE 140 
#define  GS_INTERMISSION 139 
#define  GS_LEVEL 138 
 int /*<<< orphan*/  G_DoCompleted () ; 
 int /*<<< orphan*/  G_DoLoadGame () ; 
 int /*<<< orphan*/  G_DoLoadLevel () ; 
 int /*<<< orphan*/  G_DoNewGame () ; 
 int /*<<< orphan*/  G_DoPlayDemo () ; 
 int /*<<< orphan*/  G_DoReborn (int) ; 
 int /*<<< orphan*/  G_DoSaveGame () ; 
 int /*<<< orphan*/  G_DoWorldDone () ; 
 int /*<<< orphan*/  G_ReadDemoTiccmd (TYPE_2__*) ; 
 int /*<<< orphan*/  G_WriteDemoTiccmd (TYPE_2__*) ; 
 int /*<<< orphan*/  HU_Ticker () ; 
 int /*<<< orphan*/  I_Error (char*,scalar_t__,scalar_t__) ; 
 int MAXPLAYERS ; 
 int /*<<< orphan*/  M_ScreenShot () ; 
 scalar_t__ PST_REBORN ; 
 int /*<<< orphan*/  P_Ticker () ; 
 int /*<<< orphan*/  ST_Ticker () ; 
 int /*<<< orphan*/  S_PauseSound () ; 
 int /*<<< orphan*/  S_ResumeSound () ; 
 scalar_t__ TURBOTHRESHOLD ; 
 int /*<<< orphan*/  WI_Ticker () ; 
 scalar_t__** consistancy ; 
 size_t consoleplayer ; 
 scalar_t__ demoplayback ; 
 scalar_t__ demorecording ; 
#define  ga_completed 137 
#define  ga_loadgame 136 
#define  ga_loadlevel 135 
#define  ga_newgame 134 
#define  ga_nothing 133 
#define  ga_playdemo 132 
#define  ga_savegame 131 
#define  ga_screenshot 130 
#define  ga_victory 129 
#define  ga_worlddone 128 
 int gameaction ; 
 int gamestate ; 
 int gametic ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** netcmds ; 
 int /*<<< orphan*/  netdemo ; 
 scalar_t__ netgame ; 
 int paused ; 
 scalar_t__* playeringame ; 
 TYPE_3__* players ; 
 scalar_t__ rndindex ; 
 int /*<<< orphan*/ * savedescription ; 
 int savegameslot ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 int ticdup ; 

void G_Ticker (void) 
{ 
    int		i;
    int		buf; 
    ticcmd_t*	cmd;
    
    // do player reborns if needed
    for (i=0 ; i<MAXPLAYERS ; i++) 
	if (playeringame[i] && players[i].playerstate == PST_REBORN) 
	    G_DoReborn (i);
    
    // do things to change the game state
    while (gameaction != ga_nothing) 
    { 
	switch (gameaction) 
	{ 
	  case ga_loadlevel: 
	    G_DoLoadLevel (); 
	    break; 
	  case ga_newgame: 
	    G_DoNewGame (); 
	    break; 
	  case ga_loadgame: 
	    G_DoLoadGame (); 
	    break; 
	  case ga_savegame: 
	    G_DoSaveGame (); 
	    break; 
	  case ga_playdemo: 
	    G_DoPlayDemo (); 
	    break; 
	  case ga_completed: 
	    G_DoCompleted (); 
	    break; 
	  case ga_victory: 
	    F_StartFinale (); 
	    break; 
	  case ga_worlddone: 
	    G_DoWorldDone (); 
	    break; 
	  case ga_screenshot: 
	    M_ScreenShot (); 
	    gameaction = ga_nothing; 
	    break; 
	  case ga_nothing: 
	    break; 
	} 
    }
    
    // get commands, check consistancy,
    // and build new consistancy check
    buf = (gametic/ticdup)%BACKUPTICS; 
 
    for (i=0 ; i<MAXPLAYERS ; i++)
    {
	if (playeringame[i]) 
	{ 
	    cmd = &players[i].cmd; 
 
	    memcpy (cmd, &netcmds[i][buf], sizeof(ticcmd_t)); 
 
	    if (demoplayback) 
		G_ReadDemoTiccmd (cmd); 
	    if (demorecording) 
		G_WriteDemoTiccmd (cmd);
	    
	    // check for turbo cheats
	    if (cmd->forwardmove > TURBOTHRESHOLD 
		&& !(gametic&31) && ((gametic>>5)&3) == i )
	    {
		static char turbomessage[80];
		extern char *player_names[4];
		sprintf (turbomessage, "%s is turbo!",player_names[i]);
		players[consoleplayer].message = turbomessage;
	    }
			
	    if (netgame && !netdemo && !(gametic%ticdup) ) 
	    { 
		if (gametic > BACKUPTICS 
		    && consistancy[i][buf] != cmd->consistancy) 
		{ 
		    I_Error ("consistency failure (%i should be %i)",
			     cmd->consistancy, consistancy[i][buf]); 
		} 
		if (players[i].mo) 
		    consistancy[i][buf] = players[i].mo->x; 
		else 
		    consistancy[i][buf] = rndindex; 
	    } 
	}
    }
    
    // check for special buttons
    for (i=0 ; i<MAXPLAYERS ; i++)
    {
	if (playeringame[i]) 
	{ 
	    if (players[i].cmd.buttons & BT_SPECIAL) 
	    { 
		switch (players[i].cmd.buttons & BT_SPECIALMASK) 
		{ 
		  case BTS_PAUSE: 
		    paused ^= 1; 
		    if (paused) 
			S_PauseSound (); 
		    else 
			S_ResumeSound (); 
		    break; 
					 
		  case BTS_SAVEGAME: 
		    if (!savedescription[0]) 
			strcpy (savedescription, "NET GAME"); 
		    savegameslot =  
			(players[i].cmd.buttons & BTS_SAVEMASK)>>BTS_SAVESHIFT; 
		    gameaction = ga_savegame; 
		    break; 
		} 
	    } 
	}
    }
    
    // do main actions
    switch (gamestate) 
    { 
      case GS_LEVEL: 
	P_Ticker (); 
	ST_Ticker (); 
	AM_Ticker (); 
	HU_Ticker ();            
	break; 
	 
      case GS_INTERMISSION: 
	WI_Ticker (); 
	break; 
			 
      case GS_FINALE: 
	F_Ticker (); 
	break; 
 
      case GS_DEMOSCREEN: 
	D_PageTicker (); 
	break; 
    }        
}