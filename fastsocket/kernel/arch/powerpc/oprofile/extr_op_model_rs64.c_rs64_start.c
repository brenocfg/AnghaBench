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
struct op_counter_config {int /*<<< orphan*/  event; scalar_t__ enabled; } ;

/* Variables and functions */
 unsigned int MMCR0_FC ; 
 int MSR_PMM ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  classic_ctr_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int mfmsr () ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsrd (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned int) ; 
 int num_counters ; 
 int /*<<< orphan*/ * reset_value ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int rs64_start(struct op_counter_config *ctr)
{
	int i;
	unsigned int mmcr0;

	/* set the PMM bit (see comment below) */
	mtmsrd(mfmsr() | MSR_PMM);

	for (i = 0; i < num_counters; ++i) {
		if (ctr[i].enabled) {
			classic_ctr_write(i, reset_value[i]);
			ctrl_write(i, ctr[i].event);
		} else {
			classic_ctr_write(i, 0);
		}
	}

	mmcr0 = mfspr(SPRN_MMCR0);

	/*
	 * now clear the freeze bit, counting will not start until we
	 * rfid from this excetion, because only at that point will
	 * the PMM bit be cleared
	 */
	mmcr0 &= ~MMCR0_FC;
	mtspr(SPRN_MMCR0, mmcr0);

	dbg("start on cpu %d, mmcr0 %x\n", smp_processor_id(), mmcr0);
	return 0;
}