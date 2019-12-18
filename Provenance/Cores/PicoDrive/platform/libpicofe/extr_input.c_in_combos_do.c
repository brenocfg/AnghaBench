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
 int /*<<< orphan*/  IN_BINDTYPE_EMU ; 
 size_t IN_BIND_OFFS (int,int /*<<< orphan*/ ) ; 

int in_combos_do(int keys, const int *binds, int last_key, int combo_keys, int combo_acts)
{
	int i, ret = 0;

	for (i = 0; i <= last_key; i++)
	{
		int acts, acts_c, u;

		if (!(keys & (1 << i)))
			continue;

		acts = binds[IN_BIND_OFFS(i, IN_BINDTYPE_EMU)];
		if (!acts)
			continue;

		if (!(combo_keys & (1 << i))) {
			ret |= acts;
			continue;
		}

		acts_c = acts & combo_acts;
		u = last_key;
		if (acts_c) {
			// let's try to find the other one
			for (u = i + 1; u <= last_key; u++)
				if ( (keys & (1 << u)) && (binds[IN_BIND_OFFS(u, IN_BINDTYPE_EMU)] & acts_c) ) {
					ret |= acts_c & binds[IN_BIND_OFFS(u, IN_BINDTYPE_EMU)];
					keys &= ~((1 << i) | (1 << u));
					break;
				}
		}
		// add non-combo actions if combo ones were not found
		if (u >= last_key)
			ret |= acts & ~combo_acts;
	}

	return ret;
}