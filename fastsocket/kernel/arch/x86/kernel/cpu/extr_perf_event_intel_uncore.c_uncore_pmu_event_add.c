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
struct hw_perf_event {int state; int idx; scalar_t__ last_tag; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {int n_events; scalar_t__* tags; struct perf_event** event_list; } ;

/* Variables and functions */
 int ENODEV ; 
 int PERF_EF_START ; 
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int PERF_HES_ARCH ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int UNCORE_PMC_IDX_MAX ; 
 int uncore_assign_events (struct intel_uncore_box*,int*,int) ; 
 int /*<<< orphan*/  uncore_assign_hw_event (struct intel_uncore_box*,struct perf_event*,int) ; 
 int uncore_collect_events (struct intel_uncore_box*,struct perf_event*,int) ; 
 struct intel_uncore_box* uncore_event_to_box (struct perf_event*) ; 
 int /*<<< orphan*/  uncore_pmu_event_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uncore_pmu_event_stop (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uncore_pmu_event_add(struct perf_event *event, int flags)
{
	struct intel_uncore_box *box = uncore_event_to_box(event);
	struct hw_perf_event *hwc = &event->hw;
	int assign[UNCORE_PMC_IDX_MAX];
	int i, n, ret;

	if (!box)
		return -ENODEV;

	ret = n = uncore_collect_events(box, event, false);
	if (ret < 0)
		return ret;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	if (!(flags & PERF_EF_START))
		hwc->state |= PERF_HES_ARCH;

	ret = uncore_assign_events(box, assign, n);
	if (ret)
		return ret;

	/* save events moving to new counters */
	for (i = 0; i < box->n_events; i++) {
		event = box->event_list[i];
		hwc = &event->hw;

		if (hwc->idx == assign[i] &&
			hwc->last_tag == box->tags[assign[i]])
			continue;
		/*
		 * Ensure we don't accidentally enable a stopped
		 * counter simply because we rescheduled.
		 */
		if (hwc->state & PERF_HES_STOPPED)
			hwc->state |= PERF_HES_ARCH;

		uncore_pmu_event_stop(event, PERF_EF_UPDATE);
	}

	/* reprogram moved events into new counters */
	for (i = 0; i < n; i++) {
		event = box->event_list[i];
		hwc = &event->hw;

		if (hwc->idx != assign[i] ||
			hwc->last_tag != box->tags[assign[i]])
			uncore_assign_hw_event(box, event, assign[i]);
		else if (i < box->n_events)
			continue;

		if (hwc->state & PERF_HES_ARCH)
			continue;

		uncore_pmu_event_start(event, 0);
	}
	box->n_events = n;

	return 0;
}