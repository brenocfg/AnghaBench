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
typedef  unsigned int u64 ;

/* Variables and functions */
 unsigned long MMCR0_PMC1CE ; 
 unsigned long MMCR0_PMCjCE ; 
 unsigned long MMCR1_L2SEL_SH ; 
 unsigned int MMCR1_PMC1_COMBINE_SH ; 
 unsigned int MMCR1_PMCSEL_SH (unsigned int) ; 
 int MMCR1_TTM0SEL_SH ; 
 unsigned long MMCRA_SAMPLE_ENABLE ; 
 unsigned long MMCRA_SDAR_DCACHE_MISS ; 
 unsigned long MMCRA_SDAR_ERAT_MISS ; 
 unsigned int PM_COMBINE_MSK ; 
 unsigned int PM_COMBINE_SH ; 
 unsigned int PM_L2SEL_MSK ; 
 unsigned int PM_L2SEL_SH ; 
 unsigned int PM_PMCSEL_MSK ; 
 unsigned int PM_PMC_MSK ; 
 unsigned int PM_PMC_SH ; 
 unsigned int PM_UNIT_MSK ; 
 unsigned int PM_UNIT_SH ; 
 scalar_t__ power7_marked_instr_event (unsigned int) ; 

__attribute__((used)) static int power7_compute_mmcr(u64 event[], int n_ev,
			       unsigned int hwc[], unsigned long mmcr[])
{
	unsigned long mmcr1 = 0;
	unsigned long mmcra = MMCRA_SDAR_DCACHE_MISS | MMCRA_SDAR_ERAT_MISS;
	unsigned int pmc, unit, combine, l2sel, psel;
	unsigned int pmc_inuse = 0;
	int i;

	/* First pass to count resource use */
	for (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc) {
			if (pmc > 6)
				return -1;
			if (pmc_inuse & (1 << (pmc - 1)))
				return -1;
			pmc_inuse |= 1 << (pmc - 1);
		}
	}

	/* Second pass: assign PMCs, set all MMCR1 fields */
	for (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		combine = (event[i] >> PM_COMBINE_SH) & PM_COMBINE_MSK;
		l2sel = (event[i] >> PM_L2SEL_SH) & PM_L2SEL_MSK;
		psel = event[i] & PM_PMCSEL_MSK;
		if (!pmc) {
			/* Bus event or any-PMC direct event */
			for (pmc = 0; pmc < 4; ++pmc) {
				if (!(pmc_inuse & (1 << pmc)))
					break;
			}
			if (pmc >= 4)
				return -1;
			pmc_inuse |= 1 << pmc;
		} else {
			/* Direct or decoded event */
			--pmc;
		}
		if (pmc <= 3) {
			mmcr1 |= (unsigned long) unit
				<< (MMCR1_TTM0SEL_SH - 4 * pmc);
			mmcr1 |= (unsigned long) combine
				<< (MMCR1_PMC1_COMBINE_SH - pmc);
			mmcr1 |= psel << MMCR1_PMCSEL_SH(pmc);
			if (unit == 6)	/* L2 events */
				mmcr1 |= (unsigned long) l2sel
					<< MMCR1_L2SEL_SH;
		}
		if (power7_marked_instr_event(event[i]))
			mmcra |= MMCRA_SAMPLE_ENABLE;
		hwc[i] = pmc;
	}

	/* Return MMCRx values */
	mmcr[0] = 0;
	if (pmc_inuse & 1)
		mmcr[0] = MMCR0_PMC1CE;
	if (pmc_inuse & 0x3e)
		mmcr[0] |= MMCR0_PMCjCE;
	mmcr[1] = mmcr1;
	mmcr[2] = mmcra;
	return 0;
}