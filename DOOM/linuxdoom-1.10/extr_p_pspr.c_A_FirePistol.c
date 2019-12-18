#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pspdef_t ;
struct TYPE_5__ {size_t readyweapon; int /*<<< orphan*/  refire; int /*<<< orphan*/  mo; int /*<<< orphan*/ * ammo; } ;
typedef  TYPE_1__ player_t ;
struct TYPE_6__ {size_t ammo; int /*<<< orphan*/  flashstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_BulletSlope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_GunShot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  P_SetMobjState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_SetPsprite (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_PLAY_ATK2 ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_flash ; 
 int /*<<< orphan*/  sfx_pistol ; 
 TYPE_2__* weaponinfo ; 

void
A_FirePistol
( player_t*	player,
  pspdef_t*	psp ) 
{
    S_StartSound (player->mo, sfx_pistol);

    P_SetMobjState (player->mo, S_PLAY_ATK2);
    player->ammo[weaponinfo[player->readyweapon].ammo]--;

    P_SetPsprite (player,
		  ps_flash,
		  weaponinfo[player->readyweapon].flashstate);

    P_BulletSlope (player->mo);
    P_GunShot (player->mo, !player->refire);
}