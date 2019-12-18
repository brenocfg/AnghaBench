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
typedef  int /*<<< orphan*/  pspdef_t ;
struct TYPE_4__ {size_t readyweapon; int /*<<< orphan*/  mo; int /*<<< orphan*/ * ammo; } ;
typedef  TYPE_1__ player_t ;
struct TYPE_5__ {size_t ammo; } ;

/* Variables and functions */
 scalar_t__ BFGCELLS ; 
 int /*<<< orphan*/  MT_BFG ; 
 int /*<<< orphan*/  P_SpawnPlayerMissile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* weaponinfo ; 

void
A_FireBFG
( player_t*	player,
  pspdef_t*	psp ) 
{
    player->ammo[weaponinfo[player->readyweapon].ammo] -= BFGCELLS;
    P_SpawnPlayerMissile (player->mo, MT_BFG);
}