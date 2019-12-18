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
br_des_ct_skey_expand(uint32_t *sk_exp,
	unsigned num_rounds, const uint32_t *skey)
{
	num_rounds <<= 4;
	while (num_rounds -- > 0) {
		uint32_t v, w0, w1, w2, w3;

		v = *skey ++;
		w0 = v & 0x11111111;
		w1 = (v >> 1) & 0x11111111;
		w2 = (v >> 2) & 0x11111111;
		w3 = (v >> 3) & 0x11111111;
		*sk_exp ++ = (w0 << 4) - w0;
		*sk_exp ++ = (w1 << 4) - w1;
		*sk_exp ++ = (w2 << 4) - w2;
		*sk_exp ++ = (w3 << 4) - w3;
		v = *skey ++;
		w0 = v & 0x11111111;
		w1 = (v >> 1) & 0x11111111;
		*sk_exp ++ = (w0 << 4) - w0;
		*sk_exp ++ = (w1 << 4) - w1;
	}
}