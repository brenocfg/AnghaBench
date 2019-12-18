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

__attribute__((used)) static inline void bfin_keycodecpy(unsigned short *keycode,
			const unsigned int *pdata_kc,
			unsigned short keymapsize)
{
	unsigned int i;

	for (i = 0; i < keymapsize; i++) {
		keycode[i] = pdata_kc[i] & 0xffff;
		keycode[i + keymapsize] = pdata_kc[i] >> 16;
	}
}