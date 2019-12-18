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
struct TYPE_4__ {int config1; } ;
struct hw_perf_event_extra {int config; scalar_t__ idx; scalar_t__ reg; } ;
struct hw_perf_event {struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_2__ attr; struct hw_perf_event hw; } ;
struct intel_uncore_box {TYPE_1__* pmu; } ;
struct TYPE_3__ {int pmu_idx; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 scalar_t__ SNBEP_C0_MSR_PMON_BOX_FILTER ; 
 int SNBEP_CB0_MSR_PMON_BOX_FILTER_MASK ; 
 int SNBEP_CBO_MSR_OFFSET ; 
 scalar_t__ SNBEP_PCU_MSR_PMON_BOX_FILTER ; 
 int SNBEP_PCU_MSR_PMON_BOX_FILTER_MASK ; 
 int /*<<< orphan*/  snbep_uncore_cbox ; 
 int /*<<< orphan*/  snbep_uncore_pcu ; 

__attribute__((used)) static int snbep_uncore_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;

	if (box->pmu->type == &snbep_uncore_cbox) {
		reg1->reg = SNBEP_C0_MSR_PMON_BOX_FILTER +
			SNBEP_CBO_MSR_OFFSET * box->pmu->pmu_idx;
		reg1->config = event->attr.config1 &
			SNBEP_CB0_MSR_PMON_BOX_FILTER_MASK;
	} else {
		if (box->pmu->type == &snbep_uncore_pcu) {
			reg1->reg = SNBEP_PCU_MSR_PMON_BOX_FILTER;
			reg1->config = event->attr.config1 & SNBEP_PCU_MSR_PMON_BOX_FILTER_MASK;
		} else {
			return 0;
		}
	}
	reg1->idx = 0;

	return 0;
}