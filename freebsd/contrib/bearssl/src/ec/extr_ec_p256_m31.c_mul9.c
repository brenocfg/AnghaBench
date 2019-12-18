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
 int MUL31 (int const,int const) ; 

__attribute__((used)) static void
mul9(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
	/*
	 * Maximum intermediate result is no more than
	 * 10376293531797946367, which fits in 64 bits. Reason:
	 *
	 *   10376293531797946367 = 9 * (2^30-1)^2 + 9663676406
	 *   10376293531797946367 < 9663676407 * 2^30
	 *
	 * Thus, adding together 9 products of 30-bit integers, with
	 * a carry of at most 9663676406, yields an integer that fits
	 * on 64 bits and generates a carry of at most 9663676406.
	 */
	uint64_t t[17];
	uint64_t cc;
	int i;

	t[ 0] = MUL31(a[0], b[0]);
	t[ 1] = MUL31(a[0], b[1])
		+ MUL31(a[1], b[0]);
	t[ 2] = MUL31(a[0], b[2])
		+ MUL31(a[1], b[1])
		+ MUL31(a[2], b[0]);
	t[ 3] = MUL31(a[0], b[3])
		+ MUL31(a[1], b[2])
		+ MUL31(a[2], b[1])
		+ MUL31(a[3], b[0]);
	t[ 4] = MUL31(a[0], b[4])
		+ MUL31(a[1], b[3])
		+ MUL31(a[2], b[2])
		+ MUL31(a[3], b[1])
		+ MUL31(a[4], b[0]);
	t[ 5] = MUL31(a[0], b[5])
		+ MUL31(a[1], b[4])
		+ MUL31(a[2], b[3])
		+ MUL31(a[3], b[2])
		+ MUL31(a[4], b[1])
		+ MUL31(a[5], b[0]);
	t[ 6] = MUL31(a[0], b[6])
		+ MUL31(a[1], b[5])
		+ MUL31(a[2], b[4])
		+ MUL31(a[3], b[3])
		+ MUL31(a[4], b[2])
		+ MUL31(a[5], b[1])
		+ MUL31(a[6], b[0]);
	t[ 7] = MUL31(a[0], b[7])
		+ MUL31(a[1], b[6])
		+ MUL31(a[2], b[5])
		+ MUL31(a[3], b[4])
		+ MUL31(a[4], b[3])
		+ MUL31(a[5], b[2])
		+ MUL31(a[6], b[1])
		+ MUL31(a[7], b[0]);
	t[ 8] = MUL31(a[0], b[8])
		+ MUL31(a[1], b[7])
		+ MUL31(a[2], b[6])
		+ MUL31(a[3], b[5])
		+ MUL31(a[4], b[4])
		+ MUL31(a[5], b[3])
		+ MUL31(a[6], b[2])
		+ MUL31(a[7], b[1])
		+ MUL31(a[8], b[0]);
	t[ 9] = MUL31(a[1], b[8])
		+ MUL31(a[2], b[7])
		+ MUL31(a[3], b[6])
		+ MUL31(a[4], b[5])
		+ MUL31(a[5], b[4])
		+ MUL31(a[6], b[3])
		+ MUL31(a[7], b[2])
		+ MUL31(a[8], b[1]);
	t[10] = MUL31(a[2], b[8])
		+ MUL31(a[3], b[7])
		+ MUL31(a[4], b[6])
		+ MUL31(a[5], b[5])
		+ MUL31(a[6], b[4])
		+ MUL31(a[7], b[3])
		+ MUL31(a[8], b[2]);
	t[11] = MUL31(a[3], b[8])
		+ MUL31(a[4], b[7])
		+ MUL31(a[5], b[6])
		+ MUL31(a[6], b[5])
		+ MUL31(a[7], b[4])
		+ MUL31(a[8], b[3]);
	t[12] = MUL31(a[4], b[8])
		+ MUL31(a[5], b[7])
		+ MUL31(a[6], b[6])
		+ MUL31(a[7], b[5])
		+ MUL31(a[8], b[4]);
	t[13] = MUL31(a[5], b[8])
		+ MUL31(a[6], b[7])
		+ MUL31(a[7], b[6])
		+ MUL31(a[8], b[5]);
	t[14] = MUL31(a[6], b[8])
		+ MUL31(a[7], b[7])
		+ MUL31(a[8], b[6]);
	t[15] = MUL31(a[7], b[8])
		+ MUL31(a[8], b[7]);
	t[16] = MUL31(a[8], b[8]);

	/*
	 * Propagate carries.
	 */
	cc = 0;
	for (i = 0; i < 17; i ++) {
		uint64_t w;

		w = t[i] + cc;
		d[i] = (uint32_t)w & 0x3FFFFFFF;
		cc = w >> 30;
	}
	d[17] = (uint32_t)cc;
}