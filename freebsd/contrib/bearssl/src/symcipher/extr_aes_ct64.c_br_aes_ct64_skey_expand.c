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
typedef  int uint64_t ;

/* Variables and functions */

void
br_aes_ct64_skey_expand(uint64_t *skey,
	unsigned num_rounds, const uint64_t *comp_skey)
{
	unsigned u, v, n;

	n = (num_rounds + 1) << 1;
	for (u = 0, v = 0; u < n; u ++, v += 4) {
		uint64_t x0, x1, x2, x3;

		x0 = x1 = x2 = x3 = comp_skey[u];
		x0 &= (uint64_t)0x1111111111111111;
		x1 &= (uint64_t)0x2222222222222222;
		x2 &= (uint64_t)0x4444444444444444;
		x3 &= (uint64_t)0x8888888888888888;
		x1 >>= 1;
		x2 >>= 2;
		x3 >>= 3;
		skey[v + 0] = (x0 << 4) - x0;
		skey[v + 1] = (x1 << 4) - x1;
		skey[v + 2] = (x2 << 4) - x2;
		skey[v + 3] = (x3 << 4) - x3;
	}
}