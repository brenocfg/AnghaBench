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

__attribute__((used)) static int denormal_mulf(int hx, int hy)
{
	unsigned int ix, iy;
	unsigned long long m, n;
	int exp, w;

	ix = hx & 0x7fffffff;
	iy = hy & 0x7fffffff;
	if (iy < 0x00800000 || ix == 0)
		return ((hx ^ hy) & 0x80000000);

	exp = (iy & 0x7f800000) >> 23;
	ix &= 0x007fffff;
	iy = (iy & 0x007fffff) | 0x00800000;
	m = (unsigned long long)ix * iy;
	n = m;
	w = -1;
	while (n) { n >>= 1; w++; }

	/* FIXME: use guard bits */
	exp += w - 126 - 46;
	if (exp > 0)
		ix = ((int) (m >> (w - 23)) & 0x007fffff) | (exp << 23);
	else if (exp + 22 >= 0)
		ix = (int) (m >> (w - 22 - exp)) & 0x007fffff;
	else
		ix = 0;

	ix |= (hx ^ hy) & 0x80000000;
	return ix;
}