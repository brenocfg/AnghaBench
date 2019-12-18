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

/* Variables and functions */
#define  NoState 130 
 int /*<<< orphan*/  S_ChangeMusic (int /*<<< orphan*/ ,int) ; 
#define  ShowNextLoc 129 
#define  StatCount 128 
 int /*<<< orphan*/  WI_checkForAccelerate () ; 
 int /*<<< orphan*/  WI_updateDeathmatchStats () ; 
 int /*<<< orphan*/  WI_updateNetgameStats () ; 
 int /*<<< orphan*/  WI_updateNoState () ; 
 int /*<<< orphan*/  WI_updateShowNextLoc () ; 
 int /*<<< orphan*/  WI_updateStats () ; 
 int bcnt ; 
 scalar_t__ commercial ; 
 int /*<<< orphan*/  deathmatch ; 
 scalar_t__ gamemode ; 
 int /*<<< orphan*/  mus_dm2int ; 
 int /*<<< orphan*/  mus_inter ; 
 int /*<<< orphan*/  netgame ; 
 int state ; 

void WI_Ticker(void)
{
    // counter for general background animation
    bcnt++;  

    if (bcnt == 1)
    {
	// intermission music
  	if ( gamemode == commercial )
	  S_ChangeMusic(mus_dm2int, true);
	else
	  S_ChangeMusic(mus_inter, true); 
    }

    WI_checkForAccelerate();

    switch (state)
    {
      case StatCount:
	if (deathmatch) WI_updateDeathmatchStats();
	else if (netgame) WI_updateNetgameStats();
	else WI_updateStats();
	break;
	
      case ShowNextLoc:
	WI_updateShowNextLoc();
	break;
	
      case NoState:
	WI_updateNoState();
	break;
    }

}