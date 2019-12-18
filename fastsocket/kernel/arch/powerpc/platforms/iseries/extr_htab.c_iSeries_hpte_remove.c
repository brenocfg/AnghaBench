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
 int HPTES_PER_GROUP ; 
 unsigned long HPTE_V_BOLTED ; 
 int /*<<< orphan*/  HvCallHpt_invalidateSetSwBitsGet (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iSeries_hlock (unsigned long) ; 
 unsigned long iSeries_hpte_getword0 (unsigned long) ; 
 int /*<<< orphan*/  iSeries_hunlock (unsigned long) ; 
 int mftb () ; 

__attribute__((used)) static long iSeries_hpte_remove(unsigned long hpte_group)
{
	unsigned long slot_offset;
	int i;
	unsigned long hpte_v;

	/* Pick a random slot to start at */
	slot_offset = mftb() & 0x7;

	iSeries_hlock(hpte_group);

	for (i = 0; i < HPTES_PER_GROUP; i++) {
		hpte_v = iSeries_hpte_getword0(hpte_group + slot_offset);

		if (! (hpte_v & HPTE_V_BOLTED)) {
			HvCallHpt_invalidateSetSwBitsGet(hpte_group +
							 slot_offset, 0, 0);
			iSeries_hunlock(hpte_group);
			return i;
		}

		slot_offset++;
		slot_offset &= 0x7;
	}

	iSeries_hunlock(hpte_group);

	return -1;
}