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
struct TYPE_5__ {size_t readyweapon; int /*<<< orphan*/  mo; int /*<<< orphan*/ * ammo; } ;
typedef  TYPE_1__ player_t ;
struct TYPE_6__ {size_t ammo; scalar_t__ flashstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_PLASMA ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetPsprite (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  P_SpawnPlayerMissile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_flash ; 
 TYPE_2__* weaponinfo ; 

void
A_FirePlasma
( player_t*	player,
  pspdef_t*	psp ) 
{
    player->ammo[weaponinfo[player->readyweapon].ammo]--;

    P_SetPsprite (player,
		  ps_flash,
		  weaponinfo[player->readyweapon].flashstate+(P_Random ()&1) );

    P_SpawnPlayerMissile (player->mo, MT_PLASMA);
}