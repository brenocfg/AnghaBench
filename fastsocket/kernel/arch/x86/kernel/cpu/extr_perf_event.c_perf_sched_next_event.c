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
struct TYPE_2__ {scalar_t__ weight; size_t event; scalar_t__ counter; int /*<<< orphan*/  unassigned; } ;
struct perf_sched {size_t max_events; scalar_t__ max_weight; TYPE_1__ state; struct event_constraint** constraints; } ;
struct event_constraint {scalar_t__ weight; } ;

/* Variables and functions */

__attribute__((used)) static bool perf_sched_next_event(struct perf_sched *sched)
{
	struct event_constraint *c;

	if (!sched->state.unassigned || !--sched->state.unassigned)
		return false;

	do {
		/* next event */
		sched->state.event++;
		if (sched->state.event >= sched->max_events) {
			/* next weight */
			sched->state.event = 0;
			sched->state.weight++;
			if (sched->state.weight > sched->max_weight)
				return false;
		}
		c = sched->constraints[sched->state.event];
	} while (c->weight != sched->state.weight);

	sched->state.counter = 0;	/* start with first counter */

	return true;
}