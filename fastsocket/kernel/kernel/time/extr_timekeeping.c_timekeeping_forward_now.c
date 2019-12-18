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
struct clocksource {int (* read ) (struct clocksource*) ;int cycle_last; int mask; int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int cycle_t ;
struct TYPE_2__ {int /*<<< orphan*/  raw_time; int /*<<< orphan*/  xtime; int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; struct clocksource* clock; } ;

/* Variables and functions */
 scalar_t__ arch_gettimeoffset () ; 
 int /*<<< orphan*/  clocksource_cyc2ns (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct clocksource*) ; 
 TYPE_1__ timekeeper ; 
 int /*<<< orphan*/  timespec_add_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timekeeping_forward_now(void)
{
	cycle_t cycle_now, cycle_delta;
	struct clocksource *clock;
	s64 nsec;

	clock = timekeeper.clock;
	cycle_now = clock->read(clock);
	cycle_delta = (cycle_now - clock->cycle_last) & clock->mask;
	clock->cycle_last = cycle_now;

	nsec = clocksource_cyc2ns(cycle_delta, timekeeper.mult,
				  timekeeper.shift);

	/* If arch requires, add in gettimeoffset() */
	nsec += arch_gettimeoffset();

	timespec_add_ns(&timekeeper.xtime, nsec);

	nsec = clocksource_cyc2ns(cycle_delta, clock->mult, clock->shift);
	timespec_add_ns(&timekeeper.raw_time, nsec);
}