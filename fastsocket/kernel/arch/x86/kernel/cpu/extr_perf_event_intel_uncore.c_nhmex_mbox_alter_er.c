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
typedef  int u64 ;
struct hw_perf_event_extra {int idx; int config; } ;
struct hw_perf_event {int config; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int EXTRA_REG_NHMEX_M_ZDP_CTL_FVC ; 
 int NHMEX_M_PMON_CTL_INC_SEL_SHIFT ; 
 int NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK (int) ; 
 int NHMEX_M_PMON_ZDP_CTL_FVC_MASK ; 
 int WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK (int) ; 
 int WSMEX_M_PMON_ZDP_CTL_FVC_MASK ; 
 int __BITS_VALUE (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uncore_nhmex ; 

u64 nhmex_mbox_alter_er(struct perf_event *event, int new_idx, bool modify)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;
	int idx, orig_idx = __BITS_VALUE(reg1->idx, 0, 8);
	u64 config = reg1->config;

	/* get the non-shared control bits and shift them */
	idx = orig_idx - EXTRA_REG_NHMEX_M_ZDP_CTL_FVC;
	if (uncore_nhmex)
		config &= NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
	else
		config &= WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
	if (new_idx > orig_idx) {
		idx = new_idx - orig_idx;
		config <<= 3 * idx;
	} else {
		idx = orig_idx - new_idx;
		config >>= 3 * idx;
	}

	/* add the shared control bits back */
	if (uncore_nhmex)
		config |= NHMEX_M_PMON_ZDP_CTL_FVC_MASK & reg1->config;
	else
		config |= WSMEX_M_PMON_ZDP_CTL_FVC_MASK & reg1->config;
	config |= NHMEX_M_PMON_ZDP_CTL_FVC_MASK & reg1->config;
	if (modify) {
		/* adjust the main event selector */
		if (new_idx > orig_idx)
			hwc->config += idx << NHMEX_M_PMON_CTL_INC_SEL_SHIFT;
		else
			hwc->config -= idx << NHMEX_M_PMON_CTL_INC_SEL_SHIFT;
		reg1->config = config;
		reg1->idx = ~0xff | new_idx;
	}
	return config;
}