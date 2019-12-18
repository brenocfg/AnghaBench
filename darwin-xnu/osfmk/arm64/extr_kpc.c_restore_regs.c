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
 int KPC_ARM64_PMC_COUNT ; 
 int /*<<< orphan*/  SREG_PMCR0 ; 
 int /*<<< orphan*/  SREG_PMCR1 ; 
 int /*<<< orphan*/  SREG_PMESR0 ; 
 int /*<<< orphan*/  SREG_PMESR1 ; 
 int /*<<< orphan*/  SREG_WRITE (int /*<<< orphan*/ ,int) ; 
 int cpu_number () ; 
 int /*<<< orphan*/  kpc_set_rawpmu_config (int /*<<< orphan*/ ) ; 
 int** saved_PMCR ; 
 int** saved_PMESR ; 
 int /*<<< orphan*/ * saved_RAWPMU ; 
 int /*<<< orphan*/ ** saved_counter ; 
 int /*<<< orphan*/  write_counter (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
restore_regs(void)
{
	int cpuid = cpu_number();

	/* Restore PMESR values. */
	SREG_WRITE(SREG_PMESR0, saved_PMESR[cpuid][0]);
	SREG_WRITE(SREG_PMESR1, saved_PMESR[cpuid][1]);

	kpc_set_rawpmu_config(saved_RAWPMU[cpuid]);

	/* Restore counter values */
	for (int i = 2; i < KPC_ARM64_PMC_COUNT; i++) {
		write_counter(i, saved_counter[cpuid][i]);
	}

	/* Restore PMCR0/1 values (with PMCR0 last to enable). */
	SREG_WRITE(SREG_PMCR1, saved_PMCR[cpuid][1] | 0x30303);
	SREG_WRITE(SREG_PMCR0, saved_PMCR[cpuid][0] | 0x3);
}