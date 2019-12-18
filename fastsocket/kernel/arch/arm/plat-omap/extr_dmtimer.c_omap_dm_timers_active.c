#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct omap_dm_timer {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_TIMER_CTRL_REG ; 
 int OMAP_TIMER_CTRL_ST ; 
 int dm_timer_count ; 
 struct omap_dm_timer* dm_timers ; 
 int omap_dm_timer_read_reg (struct omap_dm_timer*,int /*<<< orphan*/ ) ; 

int omap_dm_timers_active(void)
{
	int i;

	for (i = 0; i < dm_timer_count; i++) {
		struct omap_dm_timer *timer;

		timer = &dm_timers[i];

		if (!timer->enabled)
			continue;

		if (omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG) &
		    OMAP_TIMER_CTRL_ST) {
			return 1;
		}
	}
	return 0;
}