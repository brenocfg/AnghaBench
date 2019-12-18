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
struct pt_regs {int dummy; } ;
struct op_counter_config {scalar_t__ enabled; } ;

/* Variables and functions */
 unsigned int MMCR0_FC ; 
 unsigned int MMCR0_PMXE ; 
 int MSR_PMM ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_SIAR ; 
 int classic_ctr_read (int) ; 
 int /*<<< orphan*/  classic_ctr_write (int,int /*<<< orphan*/ ) ; 
 int is_kernel_addr (unsigned long) ; 
 int mfmsr () ; 
 void* mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsrd (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned int) ; 
 int num_counters ; 
 int /*<<< orphan*/  oprofile_add_ext_sample (unsigned long,struct pt_regs*,int,int) ; 
 int /*<<< orphan*/ * reset_value ; 

__attribute__((used)) static void rs64_handle_interrupt(struct pt_regs *regs,
				  struct op_counter_config *ctr)
{
	unsigned int mmcr0;
	int is_kernel;
	int val;
	int i;
	unsigned long pc = mfspr(SPRN_SIAR);

	is_kernel = is_kernel_addr(pc);

	/* set the PMM bit (see comment below) */
	mtmsrd(mfmsr() | MSR_PMM);

	for (i = 0; i < num_counters; ++i) {
		val = classic_ctr_read(i);
		if (val < 0) {
			if (ctr[i].enabled) {
				oprofile_add_ext_sample(pc, regs, i, is_kernel);
				classic_ctr_write(i, reset_value[i]);
			} else {
				classic_ctr_write(i, 0);
			}
		}
	}

	mmcr0 = mfspr(SPRN_MMCR0);

	/* reset the perfmon trigger */
	mmcr0 |= MMCR0_PMXE;

	/*
	 * now clear the freeze bit, counting will not start until we
	 * rfid from this exception, because only at that point will
	 * the PMM bit be cleared
	 */
	mmcr0 &= ~MMCR0_FC;
	mtspr(SPRN_MMCR0, mmcr0);
}