#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pspdef_t ;
struct TYPE_5__ {int* ammo; } ;
typedef  TYPE_1__ player_t ;

/* Variables and functions */
 int /*<<< orphan*/  P_CheckAmmo (TYPE_1__*) ; 
 int /*<<< orphan*/  P_SetPsprite (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_DSNR1 ; 
 size_t am_shell ; 
 int /*<<< orphan*/  ps_weapon ; 

void
A_CheckReload
( player_t*	player,
  pspdef_t*	psp )
{
    P_CheckAmmo (player);
#if 0
    if (player->ammo[am_shell]<2)
	P_SetPsprite (player, ps_weapon, S_DSNR1);
#endif
}