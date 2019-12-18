#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ buttons; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_CastTicker () ; 
 int /*<<< orphan*/  F_StartCast () ; 
 int MAXPLAYERS ; 
 int /*<<< orphan*/  S_StartMusic (int /*<<< orphan*/ ) ; 
 int TEXTSPEED ; 
 int TEXTWAIT ; 
 scalar_t__ commercial ; 
 int finalecount ; 
 int finalestage ; 
 int /*<<< orphan*/  finaletext ; 
 int /*<<< orphan*/  ga_worlddone ; 
 int /*<<< orphan*/  gameaction ; 
 int gameepisode ; 
 int gamemap ; 
 scalar_t__ gamemode ; 
 int /*<<< orphan*/  mus_bunny ; 
 TYPE_2__* players ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int wipegamestate ; 

void F_Ticker (void)
{
    int		i;
    
    // check for skipping
    if ( (gamemode == commercial)
      && ( finalecount > 50) )
    {
      // go on to the next level
      for (i=0 ; i<MAXPLAYERS ; i++)
	if (players[i].cmd.buttons)
	  break;
				
      if (i < MAXPLAYERS)
      {	
	if (gamemap == 30)
	  F_StartCast ();
	else
	  gameaction = ga_worlddone;
      }
    }
    
    // advance animation
    finalecount++;
	
    if (finalestage == 2)
    {
	F_CastTicker ();
	return;
    }
	
    if ( gamemode == commercial)
	return;
		
    if (!finalestage && finalecount>strlen (finaletext)*TEXTSPEED + TEXTWAIT)
    {
	finalecount = 0;
	finalestage = 1;
	wipegamestate = -1;		// force a wipe
	if (gameepisode == 3)
	    S_StartMusic (mus_bunny);
    }
}