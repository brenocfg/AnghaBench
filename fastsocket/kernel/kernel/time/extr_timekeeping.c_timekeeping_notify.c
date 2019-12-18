#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clocksource {int dummy; } ;
struct TYPE_2__ {struct clocksource* clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  change_clocksource ; 
 int /*<<< orphan*/  stop_machine (int /*<<< orphan*/ ,struct clocksource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_clock_notify () ; 
 TYPE_1__ timekeeper ; 

void timekeeping_notify(struct clocksource *clock)
{
	if (timekeeper.clock == clock)
		return;
	stop_machine(change_clocksource, clock, NULL);
	tick_clock_notify();
}