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
 int MMCR0_PMC1SEL_SH ; 
 int MMCR1_PMC3SEL_SH ; 
 unsigned long MMCRA_PMC8SEL0_SH ; 

__attribute__((used)) static void p4_disable_pmc(unsigned int pmc, unsigned long mmcr[])
{
	/*
	 * Setting the PMCxSEL field to 0 disables PMC x.
	 * (Note that pmc is 0-based here, not 1-based.)
	 */
	if (pmc <= 1) {
		mmcr[0] &= ~(0x1fUL << (MMCR0_PMC1SEL_SH - 7 * pmc));
	} else {
		mmcr[1] &= ~(0x1fUL << (MMCR1_PMC3SEL_SH - 5 * (pmc - 2)));
		if (pmc == 7)
			mmcr[2] &= ~(1UL << MMCRA_PMC8SEL0_SH);
	}
}