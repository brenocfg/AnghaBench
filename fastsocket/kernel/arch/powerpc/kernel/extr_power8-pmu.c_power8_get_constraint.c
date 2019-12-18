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
 unsigned long CNST_FAB_MATCH_MASK ; 
 unsigned long CNST_FAB_MATCH_VAL (int) ; 
 unsigned long CNST_L1_QUAL_MASK ; 
 unsigned long CNST_L1_QUAL_VAL (unsigned int) ; 
 unsigned long CNST_NC_MASK ; 
 unsigned long CNST_NC_VAL ; 
 unsigned long CNST_PMC_MASK (unsigned int) ; 
 unsigned long CNST_PMC_VAL (unsigned int) ; 
 unsigned long CNST_SAMPLE_MASK ; 
 unsigned long CNST_SAMPLE_VAL (int) ; 
 unsigned long CNST_THRESH_MASK ; 
 unsigned long CNST_THRESH_VAL (int) ; 
 int EVENT_CACHE_SEL_MASK ; 
 int EVENT_CACHE_SEL_SHIFT ; 
 int EVENT_IS_L1 ; 
 int EVENT_IS_MARKED ; 
 int EVENT_PMC_MASK ; 
 int EVENT_PMC_SHIFT ; 
 int EVENT_SAMPLE_SHIFT ; 
 int EVENT_THRESH_SHIFT ; 
 int EVENT_THR_CMP_MASK ; 
 int EVENT_THR_CMP_SHIFT ; 
 int EVENT_THR_CTL_SHIFT ; 
 int EVENT_UNIT_MASK ; 
 int EVENT_UNIT_SHIFT ; 
 scalar_t__ event_is_fab_match (int) ; 

__attribute__((used)) static int power8_get_constraint(u64 event, unsigned long *maskp, unsigned long *valp)
{
	unsigned int unit, pmc, cache;
	unsigned long mask, value;

	mask = value = 0;

	pmc   = (event >> EVENT_PMC_SHIFT)       & EVENT_PMC_MASK;
	unit  = (event >> EVENT_UNIT_SHIFT)      & EVENT_UNIT_MASK;
	cache = (event >> EVENT_CACHE_SEL_SHIFT) & EVENT_CACHE_SEL_MASK;

	if (pmc) {
		if (pmc > 6)
			return -1;

		mask  |= CNST_PMC_MASK(pmc);
		value |= CNST_PMC_VAL(pmc);

		if (pmc >= 5 && event != 0x500fa && event != 0x600f4)
			return -1;
	}

	if (pmc <= 4) {
		/*
		 * Add to number of counters in use. Note this includes events with
		 * a PMC of 0 - they still need a PMC, it's just assigned later.
		 * Don't count events on PMC 5 & 6, there is only one valid event
		 * on each of those counters, and they are handled above.
		 */
		mask  |= CNST_NC_MASK;
		value |= CNST_NC_VAL;
	}

	if (unit >= 6 && unit <= 9) {
		/*
		 * L2/L3 events contain a cache selector field, which is
		 * supposed to be programmed into MMCRC. However MMCRC is only
		 * HV writable, and there is no API for guest kernels to modify
		 * it. The solution is for the hypervisor to initialise the
		 * field to zeroes, and for us to only ever allow events that
		 * have a cache selector of zero.
		 */
		if (cache)
			return -1;

	} else if (event & EVENT_IS_L1) {
		mask  |= CNST_L1_QUAL_MASK;
		value |= CNST_L1_QUAL_VAL(cache);
	}

	if (event & EVENT_IS_MARKED) {
		mask  |= CNST_SAMPLE_MASK;
		value |= CNST_SAMPLE_VAL(event >> EVENT_SAMPLE_SHIFT);
	}

	/*
	 * Special case for PM_MRK_FAB_RSP_MATCH and PM_MRK_FAB_RSP_MATCH_CYC,
	 * the threshold control bits are used for the match value.
	 */
	if (event_is_fab_match(event)) {
		mask  |= CNST_FAB_MATCH_MASK;
		value |= CNST_FAB_MATCH_VAL(event >> EVENT_THR_CTL_SHIFT);
	} else {
		/*
		 * Check the mantissa upper two bits are not zero, unless the
		 * exponent is also zero. See the THRESH_CMP_MANTISSA doc.
		 */
		unsigned int cmp, exp;

		cmp = (event >> EVENT_THR_CMP_SHIFT) & EVENT_THR_CMP_MASK;
		exp = cmp >> 7;

		if (exp && (cmp & 0x60) == 0)
			return -1;

		mask  |= CNST_THRESH_MASK;
		value |= CNST_THRESH_VAL(event >> EVENT_THRESH_SHIFT);
	}

	*maskp = mask;
	*valp = value;

	return 0;
}