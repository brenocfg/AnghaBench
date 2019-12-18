#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int areasdisabled; int numareas; int /*<<< orphan*/ * areas; } ;
typedef  TYPE_1__ bot_activategoal_t ;

/* Variables and functions */
 int /*<<< orphan*/  trap_AAS_EnableRoutingArea (int /*<<< orphan*/ ,int) ; 

void BotEnableActivateGoalAreas(bot_activategoal_t *activategoal, int enable) {
	int i;

	if (activategoal->areasdisabled == !enable)
		return;
	for (i = 0; i < activategoal->numareas; i++)
		trap_AAS_EnableRoutingArea( activategoal->areas[i], enable );
	activategoal->areasdisabled = !enable;
}