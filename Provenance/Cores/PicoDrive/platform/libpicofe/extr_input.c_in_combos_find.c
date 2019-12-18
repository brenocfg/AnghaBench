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
typedef  int /*<<< orphan*/  binds ;

/* Variables and functions */
 int /*<<< orphan*/  IN_BINDTYPE_EMU ; 
 size_t IN_BIND_OFFS (int,int /*<<< orphan*/ ) ; 

void in_combos_find(const int *binds, int last_key, int *combo_keys, int *combo_acts)
{
	int act, u;

	*combo_keys = *combo_acts = 0;
	for (act = 0; act < sizeof(binds[0]) * 8; act++)
	{
		int keyc = 0;
		for (u = 0; u <= last_key; u++)
			if (binds[IN_BIND_OFFS(u, IN_BINDTYPE_EMU)] & (1 << act))
				keyc++;

		if (keyc > 1)
		{
			// loop again and mark those keys and actions as combo
			for (u = 0; u <= last_key; u++)
			{
				if (binds[IN_BIND_OFFS(u, IN_BINDTYPE_EMU)] & (1 << act)) {
					*combo_keys |= 1 << u;
					*combo_acts |= 1 << act;
				}
			}
		}
	}
}