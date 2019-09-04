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
typedef  int uint32_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int PMCR0_PMC_DISABLE_MASK (int) ; 
 int PMCR0_PMC_ENABLE_MASK (int) ; 
 int /*<<< orphan*/  SREG_PMCR0 ; 
 int SREG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SREG_WRITE (int /*<<< orphan*/ ,int) ; 
 int cpu_number () ; 
 int** saved_PMCR ; 

__attribute__((used)) static boolean_t
disable_counter(uint32_t counter)
{
	uint64_t pmcr0;
	boolean_t enabled;
	int cpuid = cpu_number();

	if (counter < 2) {
		return true;
	}

	pmcr0 = SREG_READ(SREG_PMCR0) | 0x3;
	enabled = (pmcr0 & PMCR0_PMC_ENABLE_MASK(counter)) != 0;

	if (enabled) {
		pmcr0 &= PMCR0_PMC_DISABLE_MASK(counter);
		SREG_WRITE(SREG_PMCR0, pmcr0);
	}

	saved_PMCR[cpuid][0] = pmcr0;
	return enabled;
}