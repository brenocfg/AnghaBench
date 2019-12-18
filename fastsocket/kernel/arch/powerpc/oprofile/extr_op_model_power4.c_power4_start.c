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
struct op_counter_config {scalar_t__ enabled; } ;
struct TYPE_2__ {int num_pmcs; } ;

/* Variables and functions */
 unsigned int MMCR0_FC ; 
 unsigned int MMCR0_PMAO ; 
 int MSR_PMM ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  classic_ctr_write (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* cur_cpu_spec ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int mfmsr () ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsrd (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned int) ; 
 int oprofile_running ; 
 int /*<<< orphan*/ * reset_value ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int power4_start(struct op_counter_config *ctr)
{
	int i;
	unsigned int mmcr0;

	/* set the PMM bit (see comment below) */
	mtmsrd(mfmsr() | MSR_PMM);

	for (i = 0; i < cur_cpu_spec->num_pmcs; ++i) {
		if (ctr[i].enabled) {
			classic_ctr_write(i, reset_value[i]);
		} else {
			classic_ctr_write(i, 0);
		}
	}

	mmcr0 = mfspr(SPRN_MMCR0);

	/*
	 * We must clear the PMAO bit on some (GQ) chips. Just do it
	 * all the time
	 */
	mmcr0 &= ~MMCR0_PMAO;

	/*
	 * now clear the freeze bit, counting will not start until we
	 * rfid from this excetion, because only at that point will
	 * the PMM bit be cleared
	 */
	mmcr0 &= ~MMCR0_FC;
	mtspr(SPRN_MMCR0, mmcr0);

	oprofile_running = 1;

	dbg("start on cpu %d, mmcr0 %x\n", smp_processor_id(), mmcr0);
	return 0;
}