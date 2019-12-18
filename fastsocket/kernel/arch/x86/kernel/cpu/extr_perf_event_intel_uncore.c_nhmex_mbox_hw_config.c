#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int config1; int config2; } ;
struct hw_perf_event_extra {int idx; int reg; unsigned long long config; } ;
struct TYPE_4__ {int config; struct hw_perf_event_extra branch_reg; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__ hw; } ;
struct intel_uncore_type {unsigned int msr_offset; } ;
struct intel_uncore_box {TYPE_3__* pmu; } ;
struct extra_reg {int msr; int event; int config_mask; int valid_mask; int idx; } ;
struct TYPE_6__ {unsigned int pmu_idx; struct intel_uncore_type* type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EXTRA_REG_NHMEX_M_FILTER ; 
 int EXTRA_REG_NHMEX_M_PLD ; 
 unsigned int NHMEX_M0_MSR_PMU_MM_CFG ; 
 unsigned int NHMEX_M1_MSR_PMU_MM_CFG ; 
 int NHMEX_M_PMON_MM_CFG_EN ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __BITS_VALUE (int,int,int) ; 
 int nhmex_mbox_extra_reg_idx (struct extra_reg*) ; 
 struct extra_reg* nhmex_uncore_mbox_extra_regs ; 

__attribute__((used)) static int nhmex_mbox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct intel_uncore_type *type = box->pmu->type;
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	struct hw_perf_event_extra *reg2 = &event->hw.branch_reg;
	struct extra_reg *er;
	unsigned msr;
	int reg_idx = 0;

	if (WARN_ON_ONCE(reg1->idx != -1))
		return -EINVAL;
	/*
	 * The mbox events may require 2 extra MSRs at the most. But only
	 * the lower 32 bits in these MSRs are significant, so we can use
	 * config1 to pass two MSRs' config.
	 */
	for (er = nhmex_uncore_mbox_extra_regs; er->msr; er++) {
		if (er->event != (event->hw.config & er->config_mask))
			continue;
		if (event->attr.config1 & ~er->valid_mask)
			return -EINVAL;
		if (er->idx == __BITS_VALUE(reg1->idx, 0, 8) ||
		    er->idx == __BITS_VALUE(reg1->idx, 1, 8))
			continue;
		if (WARN_ON_ONCE(reg_idx >= 2))
			return -EINVAL;

		msr = er->msr + type->msr_offset * box->pmu->pmu_idx;
		if (WARN_ON_ONCE(msr >= 0xffff || er->idx >= 0xff))
			return -EINVAL;

		/* always use the 32~63 bits to pass the PLD config */
		if (er->idx == EXTRA_REG_NHMEX_M_PLD)
			reg_idx = 1;

		reg1->idx &= ~(0xff << (reg_idx * 8));
		reg1->reg &= ~(0xffff << (reg_idx * 16));
		reg1->idx |= nhmex_mbox_extra_reg_idx(er) << (reg_idx * 8);
		reg1->reg |= msr << (reg_idx * 16);
		reg1->config = event->attr.config1;
		reg_idx++;
	}
	/* use config2 to pass the filter config */
	reg2->idx = EXTRA_REG_NHMEX_M_FILTER;
	if (event->attr.config2 & NHMEX_M_PMON_MM_CFG_EN)
		reg2->config = event->attr.config2;
	else
		reg2->config = ~0ULL;
	if (box->pmu->pmu_idx == 0)
		reg2->reg = NHMEX_M0_MSR_PMU_MM_CFG;
	else
		reg2->reg = NHMEX_M1_MSR_PMU_MM_CFG;

	return 0;
}