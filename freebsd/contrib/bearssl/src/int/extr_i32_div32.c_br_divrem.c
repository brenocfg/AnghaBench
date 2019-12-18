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
 int EQ (int,int) ; 
 int GE (int,int) ; 
 int MUX (int,int,int) ; 

uint32_t
br_divrem(uint32_t hi, uint32_t lo, uint32_t d, uint32_t *r)
{
	/* TODO: optimize this */
	uint32_t q;
	uint32_t ch, cf;
	int k;

	q = 0;
	ch = EQ(hi, d);
	hi = MUX(ch, 0, hi);
	for (k = 31; k > 0; k --) {
		int j;
		uint32_t w, ctl, hi2, lo2;

		j = 32 - k;
		w = (hi << j) | (lo >> k);
		ctl = GE(w, d) | (hi >> k);
		hi2 = (w - d) >> j;
		lo2 = lo - (d << k);
		hi = MUX(ctl, hi2, hi);
		lo = MUX(ctl, lo2, lo);
		q |= ctl << k;
	}
	cf = GE(lo, d) | hi;
	q |= cf;
	*r = MUX(cf, lo - d, lo);
	return q;
}