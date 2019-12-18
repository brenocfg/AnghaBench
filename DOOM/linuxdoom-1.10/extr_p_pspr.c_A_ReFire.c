#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pspdef_t ;
struct TYPE_6__ {int buttons; } ;
struct TYPE_7__ {scalar_t__ pendingweapon; scalar_t__ refire; scalar_t__ health; TYPE_1__ cmd; } ;
typedef  TYPE_2__ player_t ;

/* Variables and functions */
 int BT_ATTACK ; 
 int /*<<< orphan*/  P_CheckAmmo (TYPE_2__*) ; 
 int /*<<< orphan*/  P_FireWeapon (TYPE_2__*) ; 
 scalar_t__ wp_nochange ; 

void A_ReFire
( player_t*	player,
  pspdef_t*	psp )
{
    
    // check for fire
    //  (if a weaponchange is pending, let it go through instead)
    if ( (player->cmd.buttons & BT_ATTACK) 
	 && player->pendingweapon == wp_nochange
	 && player->health)
    {
	player->refire++;
	P_FireWeapon (player);
    }
    else
    {
	player->refire = 0;
	P_CheckAmmo (player);
    }
}