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
struct TYPE_2__ {int lbr_nr; int /*<<< orphan*/  lbr_sel_map; int /*<<< orphan*/  lbr_sel_mask; int /*<<< orphan*/  lbr_to; int /*<<< orphan*/  lbr_from; int /*<<< orphan*/  lbr_tos; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBR_SEL_MASK ; 
 int /*<<< orphan*/  MSR_LBR_NHM_FROM ; 
 int /*<<< orphan*/  MSR_LBR_NHM_TO ; 
 int /*<<< orphan*/  MSR_LBR_TOS ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  snb_lbr_sel_map ; 
 TYPE_1__ x86_pmu ; 

void intel_pmu_lbr_init_snb(void)
{
	x86_pmu.lbr_nr	 = 16;
	x86_pmu.lbr_tos	 = MSR_LBR_TOS;
	x86_pmu.lbr_from = MSR_LBR_NHM_FROM;
	x86_pmu.lbr_to   = MSR_LBR_NHM_TO;

	x86_pmu.lbr_sel_mask = LBR_SEL_MASK;
	x86_pmu.lbr_sel_map  = snb_lbr_sel_map;

	pr_cont("16-deep LBR, ");
}