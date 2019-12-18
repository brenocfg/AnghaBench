#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  statenum_t ;
struct TYPE_7__ {scalar_t__ sy; } ;
typedef  TYPE_1__ pspdef_t ;
struct TYPE_8__ {size_t readyweapon; } ;
typedef  TYPE_2__ player_t ;
struct TYPE_9__ {int /*<<< orphan*/  readystate; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_SetPsprite (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RAISESPEED ; 
 scalar_t__ WEAPONTOP ; 
 int /*<<< orphan*/  ps_weapon ; 
 TYPE_3__* weaponinfo ; 

void
A_Raise
( player_t*	player,
  pspdef_t*	psp )
{
    statenum_t	newstate;
	
    psp->sy -= RAISESPEED;

    if (psp->sy > WEAPONTOP )
	return;
    
    psp->sy = WEAPONTOP;
    
    // The weapon has been raised all the way,
    //  so change to the ready state.
    newstate = weaponinfo[player->readyweapon].readystate;

    P_SetPsprite (player, ps_weapon, newstate);
}