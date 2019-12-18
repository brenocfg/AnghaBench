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
typedef  int u64 ;

/* Variables and functions */
 int EVENT_CACHE_SEL_SHIFT ; 
 int EVENT_COMBINE_MASK ; 
 int EVENT_COMBINE_SHIFT ; 
 int EVENT_IS_L1 ; 
 int EVENT_IS_MARKED ; 
 int EVENT_PMC_MASK ; 
 int EVENT_PMC_SHIFT ; 
 int EVENT_PSEL_MASK ; 
 int EVENT_SAMPLE_MASK ; 
 int EVENT_SAMPLE_SHIFT ; 
 int EVENT_THR_CMP_MASK ; 
 int EVENT_THR_CMP_SHIFT ; 
 int EVENT_THR_CTL_MASK ; 
 int EVENT_THR_CTL_SHIFT ; 
 int EVENT_THR_SEL_MASK ; 
 int EVENT_THR_SEL_SHIFT ; 
 int EVENT_UNIT_MASK ; 
 int EVENT_UNIT_SHIFT ; 
 unsigned long MMCR0_PMC1CE ; 
 unsigned long MMCR0_PMCjCE ; 
 unsigned long MMCR1_COMBINE_SHIFT (unsigned int) ; 
 unsigned long MMCR1_DC_QUAL_SHIFT ; 
 unsigned long MMCR1_IC_QUAL_SHIFT ; 
 unsigned long MMCR1_PMCSEL_SHIFT (unsigned int) ; 
 unsigned long MMCR1_UNIT_SHIFT (unsigned int) ; 
 unsigned long MMCRA_SAMPLE_ENABLE ; 
 unsigned long MMCRA_SAMP_ELIG_SHIFT ; 
 unsigned long MMCRA_SAMP_MODE_SHIFT ; 
 unsigned long MMCRA_SDAR_MODE_TLB ; 
 unsigned long MMCRA_THR_CMP_SHIFT ; 
 unsigned long MMCRA_THR_CTL_SHIFT ; 
 unsigned long MMCRA_THR_SEL_SHIFT ; 
 scalar_t__ event_is_fab_match (int) ; 

__attribute__((used)) static int power8_compute_mmcr(u64 event[], int n_ev,
			       unsigned int hwc[], unsigned long mmcr[])
{
	unsigned long mmcra, mmcr1, unit, combine, psel, cache, val;
	unsigned int pmc, pmc_inuse;
	int i;

	pmc_inuse = 0;

	/* First pass to count resource use */
	for (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> EVENT_PMC_SHIFT) & EVENT_PMC_MASK;
		if (pmc)
			pmc_inuse |= 1 << pmc;
	}

	/* In continous sampling mode, update SDAR on TLB miss */
	mmcra = MMCRA_SDAR_MODE_TLB;
	mmcr1 = 0;

	/* Second pass: assign PMCs, set all MMCR1 fields */
	for (i = 0; i < n_ev; ++i) {
		pmc     = (event[i] >> EVENT_PMC_SHIFT) & EVENT_PMC_MASK;
		unit    = (event[i] >> EVENT_UNIT_SHIFT) & EVENT_UNIT_MASK;
		combine = (event[i] >> EVENT_COMBINE_SHIFT) & EVENT_COMBINE_MASK;
		psel    =  event[i] & EVENT_PSEL_MASK;

		if (!pmc) {
			for (pmc = 1; pmc <= 4; ++pmc) {
				if (!(pmc_inuse & (1 << pmc)))
					break;
			}

			pmc_inuse |= 1 << pmc;
		}

		if (pmc <= 4) {
			mmcr1 |= unit << MMCR1_UNIT_SHIFT(pmc);
			mmcr1 |= combine << MMCR1_COMBINE_SHIFT(pmc);
			mmcr1 |= psel << MMCR1_PMCSEL_SHIFT(pmc);
		}

		if (event[i] & EVENT_IS_L1) {
			cache = event[i] >> EVENT_CACHE_SEL_SHIFT;
			mmcr1 |= (cache & 1) << MMCR1_IC_QUAL_SHIFT;
			cache >>= 1;
			mmcr1 |= (cache & 1) << MMCR1_DC_QUAL_SHIFT;
		}

		if (event[i] & EVENT_IS_MARKED) {
			mmcra |= MMCRA_SAMPLE_ENABLE;

			val = (event[i] >> EVENT_SAMPLE_SHIFT) & EVENT_SAMPLE_MASK;
			if (val) {
				mmcra |= (val &  3) << MMCRA_SAMP_MODE_SHIFT;
				mmcra |= (val >> 2) << MMCRA_SAMP_ELIG_SHIFT;
			}
		}

		/*
		 * PM_MRK_FAB_RSP_MATCH and PM_MRK_FAB_RSP_MATCH_CYC,
		 * the threshold bits are used for the match value.
		 */
		if (event_is_fab_match(event[i])) {
			mmcr1 |= (event[i] >> EVENT_THR_CTL_SHIFT) &
				  EVENT_THR_CTL_MASK;
		} else {
			val = (event[i] >> EVENT_THR_CTL_SHIFT) & EVENT_THR_CTL_MASK;
			mmcra |= val << MMCRA_THR_CTL_SHIFT;
			val = (event[i] >> EVENT_THR_SEL_SHIFT) & EVENT_THR_SEL_MASK;
			mmcra |= val << MMCRA_THR_SEL_SHIFT;
			val = (event[i] >> EVENT_THR_CMP_SHIFT) & EVENT_THR_CMP_MASK;
			mmcra |= val << MMCRA_THR_CMP_SHIFT;
		}

		hwc[i] = pmc - 1;
	}

	/* Return MMCRx values */
	mmcr[0] = 0;

	/* pmc_inuse is 1-based */
	if (pmc_inuse & 2)
		mmcr[0] = MMCR0_PMC1CE;

	if (pmc_inuse & 0x7c)
		mmcr[0] |= MMCR0_PMCjCE;

	mmcr[1] = mmcr1;
	mmcr[2] = mmcra;

	return 0;
}