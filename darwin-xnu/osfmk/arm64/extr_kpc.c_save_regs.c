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

/* Variables and functions */
 scalar_t__ FALSE ; 
 int KPC_ARM64_PMC_COUNT ; 
 int /*<<< orphan*/  SREG_PMCR0 ; 
 int /*<<< orphan*/  SREG_PMESR0 ; 
 int /*<<< orphan*/  SREG_PMESR1 ; 
 int SREG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cpu_number () ; 
 int /*<<< orphan*/  kpc_get_rawpmu_config (int /*<<< orphan*/ ) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  read_counter (int) ; 
 int** saved_PMCR ; 
 int** saved_PMESR ; 
 int /*<<< orphan*/ * saved_RAWPMU ; 
 int /*<<< orphan*/ ** saved_counter ; 

__attribute__((used)) static void
save_regs(void)
{
	int cpuid = cpu_number();

	__asm__ volatile("dmb ish");

	assert(ml_get_interrupts_enabled() == FALSE);

	/* Save current PMCR0/1 values. PMCR2-4 are in the RAWPMU set. */
	saved_PMCR[cpuid][0] = SREG_READ(SREG_PMCR0) | 0x3;

	/* Save event selections. */
	saved_PMESR[cpuid][0] = SREG_READ(SREG_PMESR0);
	saved_PMESR[cpuid][1] = SREG_READ(SREG_PMESR1);

	kpc_get_rawpmu_config(saved_RAWPMU[cpuid]);

	/* Disable the counters. */
	// SREG_WRITE(SREG_PMCR0, clear);

	/* Finally, save state for each counter*/
	for (int i = 2; i < KPC_ARM64_PMC_COUNT; i++) {
		saved_counter[cpuid][i] = read_counter(i);
	}
}