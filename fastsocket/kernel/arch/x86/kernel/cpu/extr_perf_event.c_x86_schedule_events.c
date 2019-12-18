#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hw_perf_event {int idx; } ;
struct event_constraint {unsigned long* idxmsk; int /*<<< orphan*/  weight; } ;
struct cpu_hw_events {TYPE_2__** event_list; } ;
struct TYPE_5__ {struct hw_perf_event hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* put_event_constraints ) (struct cpu_hw_events*,TYPE_2__*) ;struct event_constraint* (* get_event_constraints ) (struct cpu_hw_events*,TYPE_2__*) ;} ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int ENOSPC ; 
 int X86_PMC_IDX_MAX ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int perf_assign_events (struct event_constraint**,int,int,int,int*) ; 
 struct event_constraint* stub1 (struct cpu_hw_events*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (struct cpu_hw_events*,TYPE_2__*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 TYPE_1__ x86_pmu ; 

int x86_schedule_events(struct cpu_hw_events *cpuc, int n, int *assign)
{
	struct event_constraint *c, *constraints[X86_PMC_IDX_MAX];
	unsigned long used_mask[BITS_TO_LONGS(X86_PMC_IDX_MAX)];
	int i, wmin, wmax, num = 0;
	struct hw_perf_event *hwc;

	bitmap_zero(used_mask, X86_PMC_IDX_MAX);

	for (i = 0, wmin = X86_PMC_IDX_MAX, wmax = 0; i < n; i++) {
		c = x86_pmu.get_event_constraints(cpuc, cpuc->event_list[i]);
		constraints[i] = c;
		wmin = min(wmin, c->weight);
		wmax = max(wmax, c->weight);
	}

	/*
	 * fastpath, try to reuse previous register
	 */
	for (i = 0; i < n; i++) {
		hwc = &cpuc->event_list[i]->hw;
		c = constraints[i];

		/* never assigned */
		if (hwc->idx == -1)
			break;

		/* constraint still honored */
		if (!test_bit(hwc->idx, c->idxmsk))
			break;

		/* not already used */
		if (test_bit(hwc->idx, used_mask))
			break;

		__set_bit(hwc->idx, used_mask);
		if (assign)
			assign[i] = hwc->idx;
	}

	/* slow path */
	if (i != n)
		num = perf_assign_events(constraints, n, wmin, wmax, assign);
	/*
	 * scheduling failed or is just a simulation,
	 * free resources if necessary
	 */
	if (!assign || num) {
		for (i = 0; i < n; i++) {
			if (x86_pmu.put_event_constraints)
				x86_pmu.put_event_constraints(cpuc, cpuc->event_list[i]);
		}
	}
	return num ? -ENOSPC : 0;
}