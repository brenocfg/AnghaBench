#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int buttons; } ;
struct TYPE_5__ {int attackdown; int usedown; TYPE_1__ cmd; } ;
typedef  TYPE_2__ player_t ;

/* Variables and functions */
 int BT_ATTACK ; 
 int BT_USE ; 
 int MAXPLAYERS ; 
 int acceleratestage ; 
 scalar_t__* playeringame ; 
 TYPE_2__* players ; 

void WI_checkForAccelerate(void)
{
    int   i;
    player_t  *player;

    // check for button presses to skip delays
    for (i=0, player = players ; i<MAXPLAYERS ; i++, player++)
    {
	if (playeringame[i])
	{
	    if (player->cmd.buttons & BT_ATTACK)
	    {
		if (!player->attackdown)
		    acceleratestage = 1;
		player->attackdown = true;
	    }
	    else
		player->attackdown = false;
	    if (player->cmd.buttons & BT_USE)
	    {
		if (!player->usedown)
		    acceleratestage = 1;
		player->usedown = true;
	    }
	    else
		player->usedown = false;
	}
    }
}