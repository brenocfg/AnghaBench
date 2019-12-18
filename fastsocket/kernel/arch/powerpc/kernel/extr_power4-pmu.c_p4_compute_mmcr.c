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
typedef  int /*<<< orphan*/  unituse ;
typedef  unsigned int u64 ;
typedef  int /*<<< orphan*/  busbyte ;

/* Variables and functions */
 unsigned long MMCR0_PMC1CE ; 
 int MMCR0_PMC1SEL_SH ; 
 unsigned long MMCR0_PMCjCE ; 
 unsigned int MMCR1_DEBUG0SEL_SH ; 
 int MMCR1_PMC3SEL_SH ; 
 int MMCR1_TD_CP_DBG0SEL_SH ; 
 unsigned long long MMCR1_TTC0SEL_SH ; 
 unsigned long long MMCR1_TTC1SEL_SH ; 
 unsigned long long MMCR1_TTC2SEL_SH ; 
 unsigned long long MMCR1_TTC3SEL_SH ; 
 unsigned long MMCR1_TTM0SEL_SH ; 
 unsigned long MMCR1_TTM1SEL_SH ; 
 unsigned long MMCR1_TTM2SEL_SH ; 
 unsigned int MMCRA_PMC8SEL0_SH ; 
 unsigned long MMCRA_SAMPLE_ENABLE ; 
 unsigned int PM_BYTE_MSK ; 
 unsigned int PM_BYTE_SH ; 
 unsigned int PM_LOWER_MSK ; 
 unsigned int PM_LOWER_SH ; 
 unsigned int PM_PMCSEL_MSK ; 
 unsigned int PM_PMC_MSK ; 
 unsigned int PM_PMC_SH ; 
 unsigned int PM_UNIT_MSK ; 
 unsigned int PM_UNIT_SH ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 unsigned long long* mmcr1_adder_bits ; 
 scalar_t__ p4_marked_instr_event (unsigned int) ; 

__attribute__((used)) static int p4_compute_mmcr(u64 event[], int n_ev,
			   unsigned int hwc[], unsigned long mmcr[])
{
	unsigned long mmcr0 = 0, mmcr1 = 0, mmcra = 0;
	unsigned int pmc, unit, byte, psel, lower;
	unsigned int ttm, grp;
	unsigned int pmc_inuse = 0;
	unsigned int pmc_grp_use[2];
	unsigned char busbyte[4];
	unsigned char unituse[16];
	unsigned int unitlower = 0;
	int i;

	if (n_ev > 8)
		return -1;

	/* First pass to count resource use */
	pmc_grp_use[0] = pmc_grp_use[1] = 0;
	memset(busbyte, 0, sizeof(busbyte));
	memset(unituse, 0, sizeof(unituse));
	for (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc) {
			if (pmc_inuse & (1 << (pmc - 1)))
				return -1;
			pmc_inuse |= 1 << (pmc - 1);
			/* count 1/2/5/6 vs 3/4/7/8 use */
			++pmc_grp_use[((pmc - 1) >> 1) & 1];
		}
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
		lower = (event[i] >> PM_LOWER_SH) & PM_LOWER_MSK;
		if (unit) {
			if (!pmc)
				++pmc_grp_use[byte & 1];
			if (unit == 6 || unit == 8)
				/* map alt ISU1/IFU codes: 6->2, 8->3 */
				unit = (unit >> 1) - 1;
			if (busbyte[byte] && busbyte[byte] != unit)
				return -1;
			busbyte[byte] = unit;
			lower <<= unit;
			if (unituse[unit] && lower != (unitlower & lower))
				return -1;
			unituse[unit] = 1;
			unitlower |= lower;
		}
	}
	if (pmc_grp_use[0] > 4 || pmc_grp_use[1] > 4)
		return -1;

	/*
	 * Assign resources and set multiplexer selects.
	 *
	 * Units 1,2,3 are on TTM0, 4,6,7 on TTM1, 8,10 on TTM2.
	 * Each TTMx can only select one unit, but since
	 * units 2 and 6 are both ISU1, and 3 and 8 are both IFU,
	 * we have some choices.
	 */
	if (unituse[2] & (unituse[1] | (unituse[3] & unituse[9]))) {
		unituse[6] = 1;		/* Move 2 to 6 */
		unituse[2] = 0;
	}
	if (unituse[3] & (unituse[1] | unituse[2])) {
		unituse[8] = 1;		/* Move 3 to 8 */
		unituse[3] = 0;
		unitlower = (unitlower & ~8) | ((unitlower & 8) << 5);
	}
	/* Check only one unit per TTMx */
	if (unituse[1] + unituse[2] + unituse[3] > 1 ||
	    unituse[4] + unituse[6] + unituse[7] > 1 ||
	    unituse[8] + unituse[9] > 1 ||
	    (unituse[5] | unituse[10] | unituse[11] |
	     unituse[13] | unituse[14]))
		return -1;

	/* Set TTMxSEL fields.  Note, units 1-3 => TTM0SEL codes 0-2 */
	mmcr1 |= (unsigned long)(unituse[3] * 2 + unituse[2])
		<< MMCR1_TTM0SEL_SH;
	mmcr1 |= (unsigned long)(unituse[7] * 3 + unituse[6] * 2)
		<< MMCR1_TTM1SEL_SH;
	mmcr1 |= (unsigned long)unituse[9] << MMCR1_TTM2SEL_SH;

	/* Set TTCxSEL fields. */
	if (unitlower & 0xe)
		mmcr1 |= 1ull << MMCR1_TTC0SEL_SH;
	if (unitlower & 0xf0)
		mmcr1 |= 1ull << MMCR1_TTC1SEL_SH;
	if (unitlower & 0xf00)
		mmcr1 |= 1ull << MMCR1_TTC2SEL_SH;
	if (unitlower & 0x7000)
		mmcr1 |= 1ull << MMCR1_TTC3SEL_SH;

	/* Set byte lane select fields. */
	for (byte = 0; byte < 4; ++byte) {
		unit = busbyte[byte];
		if (!unit)
			continue;
		if (unit == 0xf) {
			/* special case for GPS */
			mmcr1 |= 1ull << (MMCR1_DEBUG0SEL_SH - byte);
		} else {
			if (!unituse[unit])
				ttm = unit - 1;		/* 2->1, 3->2 */
			else
				ttm = unit >> 2;
			mmcr1 |= (unsigned long)ttm
				<< (MMCR1_TD_CP_DBG0SEL_SH - 2 * byte);
		}
	}

	/* Second pass: assign PMCs, set PMCxSEL and PMCx_ADDER_SEL fields */
	for (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
		psel = event[i] & PM_PMCSEL_MSK;
		if (!pmc) {
			/* Bus event or 00xxx direct event (off or cycles) */
			if (unit)
				psel |= 0x10 | ((byte & 2) << 2);
			for (pmc = 0; pmc < 8; ++pmc) {
				if (pmc_inuse & (1 << pmc))
					continue;
				grp = (pmc >> 1) & 1;
				if (unit) {
					if (grp == (byte & 1))
						break;
				} else if (pmc_grp_use[grp] < 4) {
					++pmc_grp_use[grp];
					break;
				}
			}
			pmc_inuse |= 1 << pmc;
		} else {
			/* Direct event */
			--pmc;
			if (psel == 0 && (byte & 2))
				/* add events on higher-numbered bus */
				mmcr1 |= 1ull << mmcr1_adder_bits[pmc];
			else if (psel == 6 && byte == 3)
				/* seem to need to set sample_enable here */
				mmcra |= MMCRA_SAMPLE_ENABLE;
			psel |= 8;
		}
		if (pmc <= 1)
			mmcr0 |= psel << (MMCR0_PMC1SEL_SH - 7 * pmc);
		else
			mmcr1 |= psel << (MMCR1_PMC3SEL_SH - 5 * (pmc - 2));
		if (pmc == 7)	/* PMC8 */
			mmcra |= (psel & 1) << MMCRA_PMC8SEL0_SH;
		hwc[i] = pmc;
		if (p4_marked_instr_event(event[i]))
			mmcra |= MMCRA_SAMPLE_ENABLE;
	}

	if (pmc_inuse & 1)
		mmcr0 |= MMCR0_PMC1CE;
	if (pmc_inuse & 0xfe)
		mmcr0 |= MMCR0_PMCjCE;

	mmcra |= 0x2000;	/* mark only one IOP per PPC instruction */

	/* Return MMCRx values */
	mmcr[0] = mmcr0;
	mmcr[1] = mmcr1;
	mmcr[2] = mmcra;
	return 0;
}