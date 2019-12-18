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
struct hw_perf_event_extra {int idx; int reg; unsigned long long config; } ;
struct hw_perf_event {int config_base; int config; struct hw_perf_event_extra branch_reg; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int NHMEX_M_PMON_ADDR_MASK_MASK ; 
 int NHMEX_M_PMON_ADDR_MASK_SHIFT ; 
 int NHMEX_M_PMON_ADDR_MATCH_MASK ; 
 int NHMEX_M_PMON_MM_CFG_EN ; 
 int NHMEX_PMON_CTL_EN_BIT0 ; 
 int __BITS_VALUE (int,int,int) ; 
 int nhmex_mbox_shared_reg_config (struct intel_uncore_box*,int) ; 
 int /*<<< orphan*/  wrmsrl (int,int) ; 

__attribute__((used)) static void nhmex_mbox_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;
	struct hw_perf_event_extra *reg2 = &hwc->branch_reg;
	int idx;

	idx = __BITS_VALUE(reg1->idx, 0, 8);
	if (idx != 0xff)
		wrmsrl(__BITS_VALUE(reg1->reg, 0, 16),
			nhmex_mbox_shared_reg_config(box, idx));
	idx = __BITS_VALUE(reg1->idx, 1, 8);
	if (idx != 0xff)
		wrmsrl(__BITS_VALUE(reg1->reg, 1, 16),
			nhmex_mbox_shared_reg_config(box, idx));

	wrmsrl(reg2->reg, 0);
	if (reg2->config != ~0ULL) {
		wrmsrl(reg2->reg + 1,
			reg2->config & NHMEX_M_PMON_ADDR_MATCH_MASK);
		wrmsrl(reg2->reg + 2, NHMEX_M_PMON_ADDR_MASK_MASK &
			(reg2->config >> NHMEX_M_PMON_ADDR_MASK_SHIFT));
		wrmsrl(reg2->reg, NHMEX_M_PMON_MM_CFG_EN);
	}

	wrmsrl(hwc->config_base, hwc->config | NHMEX_PMON_CTL_EN_BIT0);
}