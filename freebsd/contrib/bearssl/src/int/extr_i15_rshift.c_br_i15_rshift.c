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
typedef  int uint16_t ;

/* Variables and functions */

void
br_i15_rshift(uint16_t *x, int count)
{
	size_t u, len;
	unsigned r;

	len = (x[0] + 15) >> 4;
	if (len == 0) {
		return;
	}
	r = x[1] >> count;
	for (u = 2; u <= len; u ++) {
		unsigned w;

		w = x[u];
		x[u - 1] = ((w << (15 - count)) | r) & 0x7FFF;
		r = w >> count;
	}
	x[len] = r;
}