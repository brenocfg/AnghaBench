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
 int br_i31_bit_length (int*,size_t) ; 

void
br_i31_decode(uint32_t *x, const void *src, size_t len)
{
	const unsigned char *buf;
	size_t u, v;
	uint32_t acc;
	int acc_len;

	buf = src;
	u = len;
	v = 1;
	acc = 0;
	acc_len = 0;
	while (u -- > 0) {
		uint32_t b;

		b = buf[u];
		acc |= (b << acc_len);
		acc_len += 8;
		if (acc_len >= 31) {
			x[v ++] = acc & (uint32_t)0x7FFFFFFF;
			acc_len -= 31;
			acc = b >> (8 - acc_len);
		}
	}
	if (acc_len != 0) {
		x[v ++] = acc;
	}
	x[0] = br_i31_bit_length(x + 1, v - 1);
}