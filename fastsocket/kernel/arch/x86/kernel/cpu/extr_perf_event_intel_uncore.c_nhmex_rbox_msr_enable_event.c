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
struct hw_perf_event_extra {int idx; int config; int /*<<< orphan*/  reg; } ;
struct hw_perf_event {int config; int /*<<< orphan*/  config_base; struct hw_perf_event_extra branch_reg; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int NHMEX_PMON_CTL_EN_BIT0 ; 
 int NHMEX_R_PMON_CTL_EV_SEL_MASK ; 
 int nhmex_rbox_shared_reg_config (struct intel_uncore_box*,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nhmex_rbox_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;
	struct hw_perf_event_extra *reg2 = &hwc->branch_reg;
	int idx, er_idx;

	idx = reg1->idx % 6;
	er_idx = idx;
	if (er_idx > 2)
		er_idx--;
	er_idx += (reg1->idx / 6) * 5;

	switch (idx) {
	case 0:
	case 1:
		wrmsrl(reg1->reg, reg1->config);
		break;
	case 2:
	case 3:
		wrmsrl(reg1->reg, nhmex_rbox_shared_reg_config(box, er_idx));
		break;
	case 4:
	case 5:
		wrmsrl(reg1->reg, reg1->config);
		wrmsrl(reg1->reg + 1, hwc->config >> 32);
		wrmsrl(reg1->reg + 2, reg2->config);
		break;
	};

	wrmsrl(hwc->config_base, NHMEX_PMON_CTL_EN_BIT0 |
		(hwc->config & NHMEX_R_PMON_CTL_EV_SEL_MASK));
}