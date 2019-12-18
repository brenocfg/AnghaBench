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
struct hw_perf_event {scalar_t__ idx; scalar_t__ event_base; scalar_t__ config_base; scalar_t__ last_tag; int /*<<< orphan*/  last_cpu; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {scalar_t__* assign; scalar_t__* tags; } ;

/* Variables and functions */
 scalar_t__ MSR_ARCH_PERFMON_FIXED_CTR0 ; 
 scalar_t__ MSR_ARCH_PERFMON_FIXED_CTR_CTRL ; 
 scalar_t__ X86_PMC_IDX_FIXED ; 
 scalar_t__ X86_PMC_IDX_FIXED_BTS ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ x86_pmu_config_addr (scalar_t__) ; 
 scalar_t__ x86_pmu_event_addr (scalar_t__) ; 

__attribute__((used)) static inline void x86_assign_hw_event(struct perf_event *event,
				struct cpu_hw_events *cpuc, int i)
{
	struct hw_perf_event *hwc = &event->hw;

	hwc->idx = cpuc->assign[i];
	hwc->last_cpu = smp_processor_id();
	hwc->last_tag = ++cpuc->tags[i];

	if (hwc->idx == X86_PMC_IDX_FIXED_BTS) {
		hwc->config_base = 0;
		hwc->event_base	= 0;
	} else if (hwc->idx >= X86_PMC_IDX_FIXED) {
		hwc->config_base = MSR_ARCH_PERFMON_FIXED_CTR_CTRL;
		hwc->event_base = MSR_ARCH_PERFMON_FIXED_CTR0 + (hwc->idx - X86_PMC_IDX_FIXED);
	} else {
		hwc->config_base = x86_pmu_config_addr(hwc->idx);
		hwc->event_base  = x86_pmu_event_addr(hwc->idx);
	}
}