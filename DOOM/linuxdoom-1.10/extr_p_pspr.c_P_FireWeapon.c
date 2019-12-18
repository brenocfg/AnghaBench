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
typedef  int /*<<< orphan*/  statenum_t ;
struct TYPE_6__ {size_t readyweapon; int /*<<< orphan*/  mo; } ;
typedef  TYPE_1__ player_t ;
struct TYPE_7__ {int /*<<< orphan*/  atkstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_CheckAmmo (TYPE_1__*) ; 
 int /*<<< orphan*/  P_NoiseAlert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_SetMobjState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_SetPsprite (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_PLAY_ATK1 ; 
 int /*<<< orphan*/  ps_weapon ; 
 TYPE_2__* weaponinfo ; 

void P_FireWeapon (player_t* player)
{
    statenum_t	newstate;
	
    if (!P_CheckAmmo (player))
	return;
	
    P_SetMobjState (player->mo, S_PLAY_ATK1);
    newstate = weaponinfo[player->readyweapon].atkstate;
    P_SetPsprite (player, ps_weapon, newstate);
    P_NoiseAlert (player->mo, player->mo);
}