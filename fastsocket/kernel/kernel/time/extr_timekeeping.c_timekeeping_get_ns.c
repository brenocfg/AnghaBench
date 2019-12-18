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
struct clocksource {int (* read ) (struct clocksource*) ;int cycle_last; int mask; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int cycle_t ;
struct TYPE_2__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; struct clocksource* clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clocksource_cyc2ns (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct clocksource*) ; 
 TYPE_1__ timekeeper ; 

__attribute__((used)) static inline s64 timekeeping_get_ns(void)
{
	cycle_t cycle_now, cycle_delta;
	struct clocksource *clock;

	/* read clocksource: */
	clock = timekeeper.clock;
	cycle_now = clock->read(clock);

	/* calculate the delta since the last update_wall_time: */
	cycle_delta = (cycle_now - clock->cycle_last) & clock->mask;

	/* return delta convert to nanoseconds using ntp adjusted mult. */
	return clocksource_cyc2ns(cycle_delta, timekeeper.mult,
				  timekeeper.shift);
}