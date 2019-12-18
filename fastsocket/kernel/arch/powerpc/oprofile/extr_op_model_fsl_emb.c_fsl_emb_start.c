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
struct op_counter_config {scalar_t__ enabled; } ;

/* Variables and functions */
 int MSR_PMM ; 
 int /*<<< orphan*/  PMRN_PMGC0 ; 
 int /*<<< orphan*/  ctr_write (int,int /*<<< orphan*/ ) ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mfpmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int num_counters ; 
 int oprofile_running ; 
 int /*<<< orphan*/  pmc_start_ctr (int,int) ; 
 int /*<<< orphan*/  pmc_start_ctrs (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reset_value ; 
 int /*<<< orphan*/  set_pmc_marked (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int fsl_emb_start(struct op_counter_config *ctr)
{
	int i;

	mtmsr(mfmsr() | MSR_PMM);

	for (i = 0; i < num_counters; ++i) {
		if (ctr[i].enabled) {
			ctr_write(i, reset_value[i]);
			/* Set each enabled counter to only
			 * count when the Mark bit is *not* set */
			set_pmc_marked(i, 1, 0);
			pmc_start_ctr(i, 1);
		} else {
			ctr_write(i, 0);

			/* Set the ctr to be stopped */
			pmc_start_ctr(i, 0);
		}
	}

	/* Clear the freeze bit, and enable the interrupt.
	 * The counters won't actually start until the rfi clears
	 * the PMM bit */
	pmc_start_ctrs(1);

	oprofile_running = 1;

	pr_debug("start on cpu %d, pmgc0 %x\n", smp_processor_id(),
			mfpmr(PMRN_PMGC0));

	return 0;
}