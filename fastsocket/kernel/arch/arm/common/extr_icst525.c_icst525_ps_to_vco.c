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
struct icst525_vco {int s; unsigned int v; unsigned int r; } ;
struct icst525_params {unsigned int vd_max; unsigned int rd_max; unsigned long vco_max; unsigned long ref; unsigned int rd_min; unsigned int vd_min; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (size_t*) ; 
 size_t* idx2s ; 
 unsigned long* s2div ; 

struct icst525_vco
icst525_ps_to_vco(const struct icst525_params *p, unsigned long period)
{
	struct icst525_vco vco = { .s = 1, .v = p->vd_max, .r = p->rd_max };
	unsigned long f, ps;
	unsigned int i = 0, rd, best = (unsigned int)-1;

	ps = 1000000000UL / p->vco_max;

	/*
	 * First, find the PLL output divisor such
	 * that the PLL output is within spec.
	 */
	do {
		f = period / s2div[idx2s[i]];

		/*
		 * f must be between 10MHz and
		 *  320MHz (5V) or 200MHz (3V)
		 */
		if (f >= ps && f < 100000)
			break;
	} while (i < ARRAY_SIZE(idx2s));

	if (i >= ARRAY_SIZE(idx2s))
		return vco;

	vco.s = idx2s[i];

	ps = 500000000UL / p->ref;

	/*
	 * Now find the closest divisor combination
	 * which gives a PLL output of 'f'.
	 */
	for (rd = p->rd_min; rd <= p->rd_max; rd++) {
		unsigned long f_in_div, f_pll;
		unsigned int vd;
		int f_diff;

		f_in_div = ps * rd;

		vd = (f_in_div + f / 2) / f;
		if (vd < p->vd_min || vd > p->vd_max)
			continue;

		f_pll = (f_in_div + vd / 2) / vd;
		f_diff = f_pll - f;
		if (f_diff < 0)
			f_diff = -f_diff;

		if ((unsigned)f_diff < best) {
			vco.v = vd - 8;
			vco.r = rd - 2;
			if (f_diff == 0)
				break;
			best = f_diff;
		}
	}

	return vco;
}