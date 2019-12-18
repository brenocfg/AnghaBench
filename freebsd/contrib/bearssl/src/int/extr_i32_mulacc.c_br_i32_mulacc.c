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
typedef  int uint32_t ;

/* Variables and functions */
 int MUL (int,int const) ; 

void
br_i32_mulacc(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
	size_t alen, blen, u;

	alen = (a[0] + 31) >> 5;
	blen = (b[0] + 31) >> 5;
	d[0] = a[0] + b[0];
	for (u = 0; u < blen; u ++) {
		uint32_t f;
		size_t v;
#if BR_64
		uint64_t cc;
#else
		uint32_t cc;
#endif

		f = b[1 + u];
		cc = 0;
		for (v = 0; v < alen; v ++) {
			uint64_t z;

			z = (uint64_t)d[1 + u + v] + MUL(f, a[1 + v]) + cc;
			cc = z >> 32;
			d[1 + u + v] = (uint32_t)z;
		}
		d[1 + u + alen] = (uint32_t)cc;
	}
}