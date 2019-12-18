#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  playerstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_DEMOSCREEN ; 
 int /*<<< orphan*/  G_DeferedPlayDemo (char*) ; 
 int /*<<< orphan*/  PST_LIVE ; 
 int /*<<< orphan*/  S_StartMusic (int /*<<< orphan*/ ) ; 
 int advancedemo ; 
 scalar_t__ commercial ; 
 size_t consoleplayer ; 
 int demosequence ; 
 int /*<<< orphan*/  ga_nothing ; 
 int /*<<< orphan*/  gameaction ; 
 scalar_t__ gamemode ; 
 int /*<<< orphan*/  gamestate ; 
 int /*<<< orphan*/  mus_dm2ttl ; 
 int /*<<< orphan*/  mus_intro ; 
 char* pagename ; 
 int pagetic ; 
 int paused ; 
 TYPE_1__* players ; 
 scalar_t__ retail ; 
 int usergame ; 

void D_DoAdvanceDemo (void)
{
    players[consoleplayer].playerstate = PST_LIVE;  // not reborn
    advancedemo = false;
    usergame = false;               // no save / end game here
    paused = false;
    gameaction = ga_nothing;

    if ( gamemode == retail )
      demosequence = (demosequence+1)%7;
    else
      demosequence = (demosequence+1)%6;
    
    switch (demosequence)
    {
      case 0:
	if ( gamemode == commercial )
	    pagetic = 35 * 11;
	else
	    pagetic = 170;
	gamestate = GS_DEMOSCREEN;
	pagename = "TITLEPIC";
	if ( gamemode == commercial )
	  S_StartMusic(mus_dm2ttl);
	else
	  S_StartMusic (mus_intro);
	break;
      case 1:
	G_DeferedPlayDemo ("demo1");
	break;
      case 2:
	pagetic = 200;
	gamestate = GS_DEMOSCREEN;
	pagename = "CREDIT";
	break;
      case 3:
	G_DeferedPlayDemo ("demo2");
	break;
      case 4:
	gamestate = GS_DEMOSCREEN;
	if ( gamemode == commercial)
	{
	    pagetic = 35 * 11;
	    pagename = "TITLEPIC";
	    S_StartMusic(mus_dm2ttl);
	}
	else
	{
	    pagetic = 200;

	    if ( gamemode == retail )
	      pagename = "CREDIT";
	    else
	      pagename = "HELP2";
	}
	break;
      case 5:
	G_DeferedPlayDemo ("demo3");
	break;
        // THE DEFINITIVE DOOM Special Edition demo
      case 6:
	G_DeferedPlayDemo ("demo4");
	break;
    }
}