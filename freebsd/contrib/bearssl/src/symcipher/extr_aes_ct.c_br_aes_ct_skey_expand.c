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
typedef  int uint32_t ;

/* Variables and functions */

void
br_aes_ct_skey_expand(uint32_t *skey,
	unsigned num_rounds, const uint32_t *comp_skey)
{
	unsigned u, v, n;

	n = (num_rounds + 1) << 2;
	for (u = 0, v = 0; u < n; u ++, v += 2) {
		uint32_t x, y;

		x = y = comp_skey[u];
		x &= 0x55555555;
		skey[v + 0] = x | (x << 1);
		y &= 0xAAAAAAAA;
		skey[v + 1] = y | (y >> 1);
	}
}