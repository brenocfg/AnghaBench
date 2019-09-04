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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int kpc_config_t ;

/* Variables and functions */
 int CFGWORD_EL0A32EN_MASK ; 
 int CFGWORD_EL0A64EN_MASK ; 
 int CFGWORD_EL1EN_MASK ; 
 int CFGWORD_EL3EN_MASK ; 
 int PMCR1_EL0_A32_ENABLE_MASK (int /*<<< orphan*/ ) ; 
 int PMCR1_EL0_A64_ENABLE_MASK (int /*<<< orphan*/ ) ; 
 int PMCR1_EL1_A64_ENABLE_MASK (int /*<<< orphan*/ ) ; 
 int PMCR1_EL3_A64_ENABLE_MASK (int /*<<< orphan*/ ) ; 
 int PMCR1_EL_ALL_DISABLE_MASK (int /*<<< orphan*/ ) ; 
 int PMCR1_EL_ALL_ENABLE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SREG_PMCR1 ; 
 int SREG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SREG_WRITE (int /*<<< orphan*/ ,int) ; 
 int cpu_number () ; 
 int** saved_PMCR ; 

__attribute__((used)) static void
set_modes(uint32_t counter, kpc_config_t cfgword)
{
	uint64_t bits = 0;
	int cpuid = cpu_number();

	if (cfgword & CFGWORD_EL0A32EN_MASK) {
		bits |= PMCR1_EL0_A32_ENABLE_MASK(counter);
	}
	if (cfgword & CFGWORD_EL0A64EN_MASK) {
		bits |= PMCR1_EL0_A64_ENABLE_MASK(counter);
	}
	if (cfgword & CFGWORD_EL1EN_MASK) {
		bits |= PMCR1_EL1_A64_ENABLE_MASK(counter);
	}
#if !NO_MONITOR
	if (cfgword & CFGWORD_EL3EN_MASK) {
		bits |= PMCR1_EL3_A64_ENABLE_MASK(counter);
	}
#endif

	/*
	 * Backwards compatibility: Writing a non-zero configuration word with
	 * all zeros in bits 16-19 is interpreted as enabling in all modes.
	 * This matches the behavior when the PMCR1 bits weren't exposed.
	 */
	if (bits == 0 && cfgword != 0) {
		bits = PMCR1_EL_ALL_ENABLE_MASK(counter);
	}

	uint64_t pmcr1 = SREG_READ(SREG_PMCR1);
	pmcr1 &= PMCR1_EL_ALL_DISABLE_MASK(counter);
	pmcr1 |= bits;
	pmcr1 |= 0x30303; /* monotonic compatibility */
	SREG_WRITE(SREG_PMCR1, pmcr1);
	saved_PMCR[cpuid][1] = pmcr1;
}