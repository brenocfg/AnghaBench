#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int angleturn; int forwardmove; int sidemove; } ;
typedef  TYPE_1__ ticcmd_t ;
struct TYPE_7__ {TYPE_4__* mo; TYPE_1__ cmd; } ;
typedef  TYPE_2__ player_t ;
struct TYPE_8__ {scalar_t__ z; scalar_t__ floorz; int /*<<< orphan*/ * state; scalar_t__ angle; } ;

/* Variables and functions */
 scalar_t__ ANG90 ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_Thrust (TYPE_2__*,scalar_t__,int) ; 
 size_t S_PLAY ; 
 int /*<<< orphan*/  S_PLAY_RUN1 ; 
 int onground ; 
 int /*<<< orphan*/ * states ; 

void P_MovePlayer (player_t* player)
{
    ticcmd_t*		cmd;
	
    cmd = &player->cmd;
	
    player->mo->angle += (cmd->angleturn<<16);

    // Do not let the player control movement
    //  if not onground.
    onground = (player->mo->z <= player->mo->floorz);
	
    if (cmd->forwardmove && onground)
	P_Thrust (player, player->mo->angle, cmd->forwardmove*2048);
    
    if (cmd->sidemove && onground)
	P_Thrust (player, player->mo->angle-ANG90, cmd->sidemove*2048);

    if ( (cmd->forwardmove || cmd->sidemove) 
	 && player->mo->state == &states[S_PLAY] )
    {
	P_SetMobjState (player->mo, S_PLAY_RUN1);
    }
}