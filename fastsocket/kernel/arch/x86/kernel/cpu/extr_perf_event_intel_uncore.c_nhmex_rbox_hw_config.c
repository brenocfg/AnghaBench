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
struct TYPE_4__ {unsigned long long config; int /*<<< orphan*/  config2; int /*<<< orphan*/  config1; } ;
struct hw_perf_event_extra {int idx; int /*<<< orphan*/  config; int /*<<< orphan*/  reg; } ;
struct hw_perf_event {int config; struct hw_perf_event_extra branch_reg; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_2__ attr; struct hw_perf_event hw; } ;
struct intel_uncore_box {TYPE_1__* pmu; } ;
struct TYPE_3__ {int pmu_idx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_IPERF_CFG0 (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_IPERF_CFG1 (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_QLX_CFG (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_XBR_SET1_MM_CFG (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_XBR_SET2_MM_CFG (int) ; 
 int NHMEX_R_PMON_CTL_EV_SEL_MASK ; 
 int NHMEX_R_PMON_CTL_EV_SEL_SHIFT ; 

__attribute__((used)) static int nhmex_rbox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	struct hw_perf_event_extra *reg2 = &event->hw.branch_reg;
	int port, idx;

	idx = (event->hw.config & NHMEX_R_PMON_CTL_EV_SEL_MASK) >>
		NHMEX_R_PMON_CTL_EV_SEL_SHIFT;
	if (idx >= 0x18)
		return -EINVAL;

	reg1->idx = idx;
	reg1->config = event->attr.config1;

	port = idx / 6 + box->pmu->pmu_idx * 4;
	idx %= 6;
	switch (idx) {
	case 0:
		reg1->reg = NHMEX_R_MSR_PORTN_IPERF_CFG0(port);
		break;
	case 1:
		reg1->reg = NHMEX_R_MSR_PORTN_IPERF_CFG1(port);
		break;
	case 2:
	case 3:
		reg1->reg = NHMEX_R_MSR_PORTN_QLX_CFG(port);
		break;
	case 4:
	case 5:
		if (idx == 4)
			reg1->reg = NHMEX_R_MSR_PORTN_XBR_SET1_MM_CFG(port);
		else
			reg1->reg = NHMEX_R_MSR_PORTN_XBR_SET2_MM_CFG(port);
		reg2->config = event->attr.config2;
		hwc->config |= event->attr.config & (~0ULL << 32);
		break;
	};
	return 0;
}