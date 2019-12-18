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
struct op_system_config {scalar_t__ enable_user; scalar_t__ enable_kernel; int /*<<< orphan*/  mmcra; int /*<<< orphan*/  mmcr1; int /*<<< orphan*/  mmcr0; } ;
struct op_counter_config {scalar_t__ count; } ;
struct TYPE_2__ {int num_pmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMCR0_KERNEL_DISABLE ; 
 int /*<<< orphan*/  MMCR0_PROBLEM_DISABLE ; 
 int /*<<< orphan*/  PVR_POWER7p ; 
 int /*<<< orphan*/  PV_970 ; 
 int /*<<< orphan*/  PV_970FX ; 
 int /*<<< orphan*/  PV_970GX ; 
 int /*<<< orphan*/  PV_970MP ; 
 int /*<<< orphan*/  PV_POWER4 ; 
 int /*<<< orphan*/  PV_POWER4p ; 
 int /*<<< orphan*/  PV_POWER5 ; 
 int /*<<< orphan*/  PV_POWER5p ; 
 scalar_t__ __is_processor (int /*<<< orphan*/ ) ; 
 scalar_t__ cntr_marked_events ; 
 TYPE_1__* cur_cpu_spec ; 
 int /*<<< orphan*/  mmcr0_val ; 
 int /*<<< orphan*/  mmcr1_val ; 
 int /*<<< orphan*/  mmcra_val ; 
 scalar_t__ power7_marked_instr_event (int /*<<< orphan*/ ) ; 
 scalar_t__* reset_value ; 
 int use_slot_nums ; 

__attribute__((used)) static int power4_reg_setup(struct op_counter_config *ctr,
			     struct op_system_config *sys,
			     int num_ctrs)
{
	int i;

	/*
	 * The performance counter event settings are given in the mmcr0,
	 * mmcr1 and mmcra values passed from the user in the
	 * op_system_config structure (sys variable).
	 */
	mmcr0_val = sys->mmcr0;
	mmcr1_val = sys->mmcr1;
	mmcra_val = sys->mmcra;

	/* Power 7+ and newer architectures:
	 * Determine which counter events in the group (the group of events is
	 * specified by the bit settings in the MMCR1 register) are marked
	 * events for use in the interrupt handler.  Do the calculation once
	 * before OProfile starts.  Information is used in the interrupt
	 * handler.  Starting with Power 7+ we only record the sample for
	 * marked events if the SIAR valid bit is set.  For non marked events
	 * the sample is always recorded.
	 */
	if (__is_processor(PVR_POWER7p))
		cntr_marked_events = power7_marked_instr_event(mmcr1_val);
	else
		cntr_marked_events = 0; /* For older processors, set the bit map
					 * to zero so the sample will always be
					 * be recorded.
					 */

	for (i = 0; i < cur_cpu_spec->num_pmcs; ++i)
		reset_value[i] = 0x80000000UL - ctr[i].count;

	/* setup user and kernel profiling */
	if (sys->enable_kernel)
		mmcr0_val &= ~MMCR0_KERNEL_DISABLE;
	else
		mmcr0_val |= MMCR0_KERNEL_DISABLE;

	if (sys->enable_user)
		mmcr0_val &= ~MMCR0_PROBLEM_DISABLE;
	else
		mmcr0_val |= MMCR0_PROBLEM_DISABLE;

	if (__is_processor(PV_POWER4) || __is_processor(PV_POWER4p) ||
	    __is_processor(PV_970) || __is_processor(PV_970FX) ||
	    __is_processor(PV_970MP) || __is_processor(PV_970GX) ||
	    __is_processor(PV_POWER5) || __is_processor(PV_POWER5p))
		use_slot_nums = 1;

	return 0;
}