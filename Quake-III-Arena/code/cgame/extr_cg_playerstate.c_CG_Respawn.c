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
struct TYPE_6__ {TYPE_2__* snap; int /*<<< orphan*/  weaponSelect; int /*<<< orphan*/  time; int /*<<< orphan*/  weaponSelectTime; int /*<<< orphan*/  thisFrameTeleport; } ;
struct TYPE_4__ {int /*<<< orphan*/  weapon; } ;
struct TYPE_5__ {TYPE_1__ ps; } ;

/* Variables and functions */
 TYPE_3__ cg ; 
 int /*<<< orphan*/  qtrue ; 

void CG_Respawn( void ) {
	// no error decay on player movement
	cg.thisFrameTeleport = qtrue;

	// display weapons available
	cg.weaponSelectTime = cg.time;

	// select the weapon the server says we are using
	cg.weaponSelect = cg.snap->ps.weapon;
}