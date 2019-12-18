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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void
finish_mod(uint16_t *a, size_t len, const uint16_t *m, uint32_t neg)
{
	size_t k;
	uint32_t cc, xm, ym;

	/*
	 * First pass: compare a (assumed nonnegative) with m.
	 */
	cc = 0;
	for (k = 0; k < len; k ++) {
		uint32_t aw, mw;

		aw = a[k];
		mw = m[k];
		cc = (aw - mw - cc) >> 31;
	}

	/*
	 * At this point:
	 *   if neg = 1, then we must add m (regardless of cc)
	 *   if neg = 0 and cc = 0, then we must subtract m
	 *   if neg = 0 and cc = 1, then we must do nothing
	 */
	xm = 0x7FFF & -neg;
	ym = -(neg | (1 - cc));
	cc = neg;
	for (k = 0; k < len; k ++) {
		uint32_t aw, mw;

		aw = a[k];
		mw = (m[k] ^ xm) & ym;
		aw = aw - mw - cc;
		a[k] = aw & 0x7FFF;
		cc = aw >> 31;
	}
}