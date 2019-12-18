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
struct hw_perf_event {size_t idx; int state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {scalar_t__ n_active; int /*<<< orphan*/ ** events; int /*<<< orphan*/  active_mask; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ __test_and_clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uncore_disable_box (struct intel_uncore_box*) ; 
 int /*<<< orphan*/  uncore_disable_event (struct intel_uncore_box*,struct perf_event*) ; 
 struct intel_uncore_box* uncore_event_to_box (struct perf_event*) ; 
 int /*<<< orphan*/  uncore_perf_event_update (struct intel_uncore_box*,struct perf_event*) ; 
 int /*<<< orphan*/  uncore_pmu_cancel_hrtimer (struct intel_uncore_box*) ; 

__attribute__((used)) static void uncore_pmu_event_stop(struct perf_event *event, int flags)
{
	struct intel_uncore_box *box = uncore_event_to_box(event);
	struct hw_perf_event *hwc = &event->hw;

	if (__test_and_clear_bit(hwc->idx, box->active_mask)) {
		uncore_disable_event(box, event);
		box->n_active--;
		box->events[hwc->idx] = NULL;
		WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
		hwc->state |= PERF_HES_STOPPED;

		if (box->n_active == 0) {
			uncore_disable_box(box);
			uncore_pmu_cancel_hrtimer(box);
		}
	}

	if ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) {
		/*
		 * Drain the remaining delta count out of a event
		 * that we are disabling:
		 */
		uncore_perf_event_update(box, event);
		hwc->state |= PERF_HES_UPTODATE;
	}
}