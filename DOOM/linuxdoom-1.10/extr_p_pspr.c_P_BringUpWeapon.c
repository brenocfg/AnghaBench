#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  statenum_t ;
struct TYPE_7__ {size_t pendingweapon; size_t readyweapon; TYPE_1__* psprites; int /*<<< orphan*/  mo; } ;
typedef  TYPE_2__ player_t ;
struct TYPE_8__ {int /*<<< orphan*/  upstate; } ;
struct TYPE_6__ {int /*<<< orphan*/  sy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_SetPsprite (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEAPONBOTTOM ; 
 size_t ps_weapon ; 
 int /*<<< orphan*/  sfx_sawup ; 
 TYPE_3__* weaponinfo ; 
 size_t wp_chainsaw ; 
 size_t wp_nochange ; 

void P_BringUpWeapon (player_t* player)
{
    statenum_t	newstate;
	
    if (player->pendingweapon == wp_nochange)
	player->pendingweapon = player->readyweapon;
		
    if (player->pendingweapon == wp_chainsaw)
	S_StartSound (player->mo, sfx_sawup);
		
    newstate = weaponinfo[player->pendingweapon].upstate;

    player->pendingweapon = wp_nochange;
    player->psprites[ps_weapon].sy = WEAPONBOTTOM;

    P_SetPsprite (player, ps_weapon, newstate);
}