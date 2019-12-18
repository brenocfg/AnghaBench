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
#define  ShowNextLoc 129 
#define  StatCount 128 
 int /*<<< orphan*/  WI_drawDeathmatchStats () ; 
 int /*<<< orphan*/  WI_drawNetgameStats () ; 
 int /*<<< orphan*/  WI_drawNoState () ; 
 int /*<<< orphan*/  WI_drawShowNextLoc () ; 
 int /*<<< orphan*/  WI_drawStats () ; 
 int /*<<< orphan*/  deathmatch ; 
 int /*<<< orphan*/  netgame ; 
 int state ; 

void WI_Drawer (void)
{
    switch (state)
    {
      case StatCount:
	if (deathmatch)
	    WI_drawDeathmatchStats();
	else if (netgame)
	    WI_drawNetgameStats();
	else
	    WI_drawStats();
	break;
	
      case ShowNextLoc:
	WI_drawShowNextLoc();
	break;
	
      case NoState:
	WI_drawNoState();
	break;
    }
}