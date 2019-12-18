#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ freq; } ;
struct hw_perf_event {unsigned int config; int sample_period; } ;
struct perf_event {TYPE_1__ attr; struct hw_perf_event hw; } ;
struct event_constraint {int dummy; } ;
struct TYPE_4__ {unsigned int (* event_map ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned int INTEL_ARCH_EVENT_MASK ; 
 int /*<<< orphan*/  PERF_COUNT_HW_BRANCH_INSTRUCTIONS ; 
 struct event_constraint bts_constraint ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static struct event_constraint *
intel_bts_constraints(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	unsigned int hw_event, bts_event;

	if (event->attr.freq)
		return NULL;

	hw_event = hwc->config & INTEL_ARCH_EVENT_MASK;
	bts_event = x86_pmu.event_map(PERF_COUNT_HW_BRANCH_INSTRUCTIONS);

	if (unlikely(hw_event == bts_event && hwc->sample_period == 1))
		return &bts_constraint;

	return NULL;
}