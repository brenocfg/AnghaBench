#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int viewz; } ;

/* Variables and functions */
 int MAXPLAYERS ; 
 int /*<<< orphan*/  P_PlayerThink (TYPE_1__*) ; 
 int /*<<< orphan*/  P_RespawnSpecials () ; 
 int /*<<< orphan*/  P_RunThinkers () ; 
 int /*<<< orphan*/  P_UpdateSpecials () ; 
 size_t consoleplayer ; 
 int /*<<< orphan*/  demoplayback ; 
 int /*<<< orphan*/  leveltime ; 
 scalar_t__ menuactive ; 
 int /*<<< orphan*/  netgame ; 
 scalar_t__ paused ; 
 scalar_t__* playeringame ; 
 TYPE_1__* players ; 

void P_Ticker (void)
{
    int		i;
    
    // run the tic
    if (paused)
	return;
		
    // pause if in menu and at least one tic has been run
    if ( !netgame
	 && menuactive
	 && !demoplayback
	 && players[consoleplayer].viewz != 1)
    {
	return;
    }
    
		
    for (i=0 ; i<MAXPLAYERS ; i++)
	if (playeringame[i])
	    P_PlayerThink (&players[i]);
			
    P_RunThinkers ();
    P_UpdateSpecials ();
    P_RespawnSpecials ();

    // for par times
    leveltime++;	
}