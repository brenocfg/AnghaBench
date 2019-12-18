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
struct hw_perf_event {int idx; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct event_constraint {int dummy; } ;
struct cpu_hw_events {struct amd_nb* amd_nb; } ;
struct amd_nb {struct event_constraint* event_constraints; struct perf_event** owners; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 scalar_t__ amd_has_nb (struct cpu_hw_events*) ; 
 scalar_t__ amd_is_nb_event (struct hw_perf_event*) ; 
 struct perf_event* cmpxchg (struct perf_event**,int /*<<< orphan*/ *,struct perf_event*) ; 
 struct event_constraint emptyconstraint ; 
 struct event_constraint unconstrained ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static struct event_constraint *
amd_get_event_constraints(struct cpu_hw_events *cpuc, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct amd_nb *nb = cpuc->amd_nb;
	struct perf_event *old = NULL;
	int max = x86_pmu.num_counters;
	int i, j, k = -1;

	/*
	 * if not NB event or no NB, then no constraints
	 */
	if (!(amd_has_nb(cpuc) && amd_is_nb_event(hwc)))
		return &unconstrained;

	/*
	 * detect if already present, if so reuse
	 *
	 * cannot merge with actual allocation
	 * because of possible holes
	 *
	 * event can already be present yet not assigned (in hwc->idx)
	 * because of successive calls to x86_schedule_events() from
	 * hw_perf_group_sched_in() without hw_perf_enable()
	 */
	for (i = 0; i < max; i++) {
		/*
		 * keep track of first free slot
		 */
		if (k == -1 && !nb->owners[i])
			k = i;

		/* already present, reuse */
		if (nb->owners[i] == event)
			goto done;
	}
	/*
	 * not present, so grab a new slot
	 * starting either at:
	 */
	if (hwc->idx != -1) {
		/* previous assignment */
		i = hwc->idx;
	} else if (k != -1) {
		/* start from free slot found */
		i = k;
	} else {
		/*
		 * event not found, no slot found in
		 * first pass, try again from the
		 * beginning
		 */
		i = 0;
	}
	j = i;
	do {
		old = cmpxchg(nb->owners+i, NULL, event);
		if (!old)
			break;
		if (++i == max)
			i = 0;
	} while (i != j);
done:
	if (!old)
		return &nb->event_constraints[i];

	return &emptyconstraint;
}