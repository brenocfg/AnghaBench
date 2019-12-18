#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {int unit; unsigned long mask; unsigned long value; int lowerbit; } ;

/* Variables and functions */
 int PM_BYTE_MSK ; 
 int PM_BYTE_SH ; 
 int PM_LOWER_MSK ; 
 int PM_LOWER_SH ; 
 int PM_PMCSEL_MSK ; 
 int PM_PMC_MSK ; 
 int PM_PMC_SH ; 
 int PM_UNIT_MSK ; 
 int PM_UNIT_SH ; 
 scalar_t__ p4_marked_instr_event (int) ; 
 TYPE_1__* p4_unitinfo ; 

__attribute__((used)) static int p4_get_constraint(u64 event, unsigned long *maskp,
			     unsigned long *valp)
{
	int pmc, byte, unit, lower, sh;
	unsigned long mask = 0, value = 0;
	int grp = -1;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > 8)
			return -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		value |= 1 << sh;
		grp = ((pmc - 1) >> 1) & 1;
	}
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
	if (unit) {
		lower = (event >> PM_LOWER_SH) & PM_LOWER_MSK;

		/*
		 * Bus events on bytes 0 and 2 can be counted
		 * on PMC1/2/5/6; bytes 1 and 3 on PMC3/4/7/8.
		 */
		if (!pmc)
			grp = byte & 1;

		if (!p4_unitinfo[unit].unit)
			return -1;
		mask  |= p4_unitinfo[unit].mask;
		value |= p4_unitinfo[unit].value;
		sh = p4_unitinfo[unit].lowerbit;
		if (sh > 1)
			value |= (unsigned long)lower << sh;
		else if (lower != sh)
			return -1;
		unit = p4_unitinfo[unit].unit;

		/* Set byte lane select field */
		mask  |= 0xfULL << (28 - 4 * byte);
		value |= (unsigned long)unit << (28 - 4 * byte);
	}
	if (grp == 0) {
		/* increment PMC1/2/5/6 field */
		mask  |= 0x8000000000ull;
		value |= 0x1000000000ull;
	} else {
		/* increment PMC3/4/7/8 field */
		mask  |= 0x800000000ull;
		value |= 0x100000000ull;
	}

	/* Marked instruction events need sample_enable set */
	if (p4_marked_instr_event(event)) {
		mask  |= 1ull << 56;
		value |= 1ull << 56;
	}

	/* PMCSEL=6 decode events on byte 2 need sample_enable clear */
	if (pmc && (event & PM_PMCSEL_MSK) == 6 && byte == 2)
		mask  |= 1ull << 56;

	*maskp = mask;
	*valp = value;
	return 0;
}