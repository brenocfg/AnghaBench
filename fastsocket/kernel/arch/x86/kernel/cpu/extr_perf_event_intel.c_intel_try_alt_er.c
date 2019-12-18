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
struct TYPE_4__ {int idx; int /*<<< orphan*/  reg; } ;
struct TYPE_5__ {int config; TYPE_1__ extra_reg; } ;
struct perf_event {TYPE_2__ hw; } ;
struct TYPE_6__ {int er_flags; } ;

/* Variables and functions */
 int ERF_HAS_RSP_1 ; 
 int EXTRA_REG_RSP_0 ; 
 int EXTRA_REG_RSP_1 ; 
 int INTEL_ARCH_EVENT_MASK ; 
 int /*<<< orphan*/  MSR_OFFCORE_RSP_0 ; 
 int /*<<< orphan*/  MSR_OFFCORE_RSP_1 ; 
 TYPE_3__ x86_pmu ; 

__attribute__((used)) static bool intel_try_alt_er(struct perf_event *event, int orig_idx)
{
	if (!(x86_pmu.er_flags & ERF_HAS_RSP_1))
		return false;

	if (event->hw.extra_reg.idx == EXTRA_REG_RSP_0) {
		event->hw.config &= ~INTEL_ARCH_EVENT_MASK;
		event->hw.config |= 0x01bb;
		event->hw.extra_reg.idx = EXTRA_REG_RSP_1;
		event->hw.extra_reg.reg = MSR_OFFCORE_RSP_1;
	} else if (event->hw.extra_reg.idx == EXTRA_REG_RSP_1) {
		event->hw.config &= ~INTEL_ARCH_EVENT_MASK;
		event->hw.config |= 0x01b7;
		event->hw.extra_reg.idx = EXTRA_REG_RSP_0;
		event->hw.extra_reg.reg = MSR_OFFCORE_RSP_0;
	}

	if (event->hw.extra_reg.idx == orig_idx)
		return false;

	return true;
}