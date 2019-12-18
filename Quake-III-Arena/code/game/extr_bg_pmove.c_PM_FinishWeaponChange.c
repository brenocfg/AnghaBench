#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int weapon; } ;
struct TYPE_6__ {TYPE_2__* ps; TYPE_1__ cmd; } ;
struct TYPE_5__ {int* stats; int weapon; int weaponTime; int /*<<< orphan*/  weaponstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_StartTorsoAnim (int /*<<< orphan*/ ) ; 
 size_t STAT_WEAPONS ; 
 int /*<<< orphan*/  TORSO_RAISE ; 
 int /*<<< orphan*/  WEAPON_RAISING ; 
 int WP_NONE ; 
 int WP_NUM_WEAPONS ; 
 TYPE_3__* pm ; 

__attribute__((used)) static void PM_FinishWeaponChange( void ) {
	int		weapon;

	weapon = pm->cmd.weapon;
	if ( weapon < WP_NONE || weapon >= WP_NUM_WEAPONS ) {
		weapon = WP_NONE;
	}

	if ( !( pm->ps->stats[STAT_WEAPONS] & ( 1 << weapon ) ) ) {
		weapon = WP_NONE;
	}

	pm->ps->weapon = weapon;
	pm->ps->weaponstate = WEAPON_RAISING;
	pm->ps->weaponTime += 250;
	PM_StartTorsoAnim( TORSO_RAISE );
}