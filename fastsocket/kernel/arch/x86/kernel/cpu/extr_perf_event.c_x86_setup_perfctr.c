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
typedef  long long u64 ;
struct perf_event_attr {scalar_t__ type; scalar_t__ config; int /*<<< orphan*/  exclude_kernel; int /*<<< orphan*/  freq; } ;
struct hw_perf_event {int sample_period; int last_period; long long config; int /*<<< orphan*/  period_left; } ;
struct perf_event {struct hw_perf_event hw; struct perf_event_attr attr; } ;
struct TYPE_2__ {int max_period; scalar_t__ max_events; long long (* event_map ) (scalar_t__) ;int /*<<< orphan*/  bts_active; int /*<<< orphan*/  apic; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 scalar_t__ PERF_COUNT_HW_BRANCH_INSTRUCTIONS ; 
 scalar_t__ PERF_TYPE_HW_CACHE ; 
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  is_sampling_event (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int) ; 
 int set_ext_hw_attr (struct hw_perf_event*,struct perf_event*) ; 
 long long stub1 (scalar_t__) ; 
 TYPE_1__ x86_pmu ; 

int x86_setup_perfctr(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	struct hw_perf_event *hwc = &event->hw;
	u64 config;

	if (!is_sampling_event(event)) {
		hwc->sample_period = x86_pmu.max_period;
		hwc->last_period = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	} else {
		/*
		 * If we have a PMU initialized but no APIC
		 * interrupts, we cannot sample hardware
		 * events (user-space has to fall back and
		 * sample via a hrtimer based software event):
		 */
		if (!x86_pmu.apic)
			return -EOPNOTSUPP;
	}

	/*
	 * Do not allow config1 (extended registers) to propagate,
	 * there's no sane user-space generalization yet:
	 */
	if (attr->type == PERF_TYPE_RAW)
		return 0;

	if (attr->type == PERF_TYPE_HW_CACHE)
		return set_ext_hw_attr(hwc, event);

	if (attr->config >= x86_pmu.max_events)
		return -EINVAL;

	/*
	 * The generic map:
	 */
	config = x86_pmu.event_map(attr->config);

	if (config == 0)
		return -ENOENT;

	if (config == -1LL)
		return -EINVAL;

	/*
	 * Branch tracing:
	 */
	if (attr->config == PERF_COUNT_HW_BRANCH_INSTRUCTIONS &&
	    !attr->freq && hwc->sample_period == 1) {
		/* BTS is not supported by this architecture. */
		if (!x86_pmu.bts_active)
			return -EOPNOTSUPP;

		/* BTS is currently only allowed for user-mode. */
		if (!attr->exclude_kernel)
			return -EOPNOTSUPP;
	}

	hwc->config |= config;

	return 0;
}