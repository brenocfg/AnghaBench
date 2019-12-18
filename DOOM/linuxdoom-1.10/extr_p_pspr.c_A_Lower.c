#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sy; } ;
typedef  TYPE_1__ pspdef_t ;
struct TYPE_8__ {scalar_t__ playerstate; int /*<<< orphan*/  pendingweapon; int /*<<< orphan*/  readyweapon; int /*<<< orphan*/  health; } ;
typedef  TYPE_2__ player_t ;

/* Variables and functions */
 scalar_t__ LOWERSPEED ; 
 scalar_t__ PST_DEAD ; 
 int /*<<< orphan*/  P_BringUpWeapon (TYPE_2__*) ; 
 int /*<<< orphan*/  P_SetPsprite (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_NULL ; 
 scalar_t__ WEAPONBOTTOM ; 
 int /*<<< orphan*/  ps_weapon ; 

void
A_Lower
( player_t*	player,
  pspdef_t*	psp )
{	
    psp->sy += LOWERSPEED;

    // Is already down.
    if (psp->sy < WEAPONBOTTOM )
	return;

    // Player is dead.
    if (player->playerstate == PST_DEAD)
    {
	psp->sy = WEAPONBOTTOM;

	// don't bring weapon back up
	return;		
    }
    
    // The old weapon has been lowered off the screen,
    // so change the weapon and start raising it
    if (!player->health)
    {
	// Player is dead, so keep the weapon off screen.
	P_SetPsprite (player,  ps_weapon, S_NULL);
	return;	
    }
	
    player->readyweapon = player->pendingweapon; 

    P_BringUpWeapon (player);
}