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
square9(uint32_t *d, const uint32_t *a)
{
	uint64_t t[17];
	uint64_t cc;
	int i;

	t[ 0] = MUL31(a[0], a[0]);
	t[ 1] = ((MUL31(a[0], a[1])) << 1);
	t[ 2] = MUL31(a[1], a[1])
		+ ((MUL31(a[0], a[2])) << 1);
	t[ 3] = ((MUL31(a[0], a[3])
		+ MUL31(a[1], a[2])) << 1);
	t[ 4] = MUL31(a[2], a[2])
		+ ((MUL31(a[0], a[4])
		+ MUL31(a[1], a[3])) << 1);
	t[ 5] = ((MUL31(a[0], a[5])
		+ MUL31(a[1], a[4])
		+ MUL31(a[2], a[3])) << 1);
	t[ 6] = MUL31(a[3], a[3])
		+ ((MUL31(a[0], a[6])
		+ MUL31(a[1], a[5])
		+ MUL31(a[2], a[4])) << 1);
	t[ 7] = ((MUL31(a[0], a[7])
		+ MUL31(a[1], a[6])
		+ MUL31(a[2], a[5])
		+ MUL31(a[3], a[4])) << 1);
	t[ 8] = MUL31(a[4], a[4])
		+ ((MUL31(a[0], a[8])
		+ MUL31(a[1], a[7])
		+ MUL31(a[2], a[6])
		+ MUL31(a[3], a[5])) << 1);
	t[ 9] = ((MUL31(a[1], a[8])
		+ MUL31(a[2], a[7])
		+ MUL31(a[3], a[6])
		+ MUL31(a[4], a[5])) << 1);
	t[10] = MUL31(a[5], a[5])
		+ ((MUL31(a[2], a[8])
		+ MUL31(a[3], a[7])
		+ MUL31(a[4], a[6])) << 1);
	t[11] = ((MUL31(a[3], a[8])
		+ MUL31(a[4], a[7])
		+ MUL31(a[5], a[6])) << 1);
	t[12] = MUL31(a[6], a[6])
		+ ((MUL31(a[4], a[8])
		+ MUL31(a[5], a[7])) << 1);
	t[13] = ((MUL31(a[5], a[8])
		+ MUL31(a[6], a[7])) << 1);
	t[14] = MUL31(a[7], a[7])
		+ ((MUL31(a[6], a[8])) << 1);
	t[15] = ((MUL31(a[7], a[8])) << 1);
	t[16] = MUL31(a[8], a[8]);

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