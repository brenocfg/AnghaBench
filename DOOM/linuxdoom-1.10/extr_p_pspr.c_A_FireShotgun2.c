#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pspdef_t ;
struct TYPE_9__ {int* ammo; size_t readyweapon; TYPE_3__* mo; } ;
typedef  TYPE_1__ player_t ;
typedef  int angle_t ;
struct TYPE_11__ {int angle; } ;
struct TYPE_10__ {size_t ammo; int /*<<< orphan*/  flashstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISSILERANGE ; 
 int /*<<< orphan*/  P_BulletSlope (TYPE_3__*) ; 
 int /*<<< orphan*/  P_LineAttack (TYPE_3__*,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_SetPsprite (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_PLAY_ATK2 ; 
 int /*<<< orphan*/  S_StartSound (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bulletslope ; 
 int /*<<< orphan*/  ps_flash ; 
 int /*<<< orphan*/  sfx_dshtgn ; 
 TYPE_2__* weaponinfo ; 

void
A_FireShotgun2
( player_t*	player,
  pspdef_t*	psp ) 
{
    int		i;
    angle_t	angle;
    int		damage;
		
	
    S_StartSound (player->mo, sfx_dshtgn);
    P_SetMobjState (player->mo, S_PLAY_ATK2);

    player->ammo[weaponinfo[player->readyweapon].ammo]-=2;

    P_SetPsprite (player,
		  ps_flash,
		  weaponinfo[player->readyweapon].flashstate);

    P_BulletSlope (player->mo);
	
    for (i=0 ; i<20 ; i++)
    {
	damage = 5*(P_Random ()%3+1);
	angle = player->mo->angle;
	angle += (P_Random()-P_Random())<<19;
	P_LineAttack (player->mo,
		      angle,
		      MISSILERANGE,
		      bulletslope + ((P_Random()-P_Random())<<5), damage);
    }
}