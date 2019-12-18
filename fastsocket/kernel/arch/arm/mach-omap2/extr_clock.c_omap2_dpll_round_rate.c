#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dpll_data {unsigned long max_multiplier; long last_rounded_rate; int min_divider; int max_divider; int rate_tolerance; int last_rounded_m; int last_rounded_n; TYPE_1__* clk_ref; } ;
struct clk {long name; struct dpll_data* dpll_data; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 int DPLL_FINT_INVALID ; 
 int DPLL_FINT_UNDERFLOW ; 
 int DPLL_MULT_UNDERFLOW ; 
 unsigned long DPLL_SCALE_FACTOR ; 
 long _dpll_compute_new_rate (unsigned long,int,int) ; 
 int _dpll_test_fint (struct clk*,int) ; 
 int _dpll_test_mult (int*,int,unsigned long*,unsigned long,unsigned long) ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

long omap2_dpll_round_rate(struct clk *clk, unsigned long target_rate)
{
	int m, n, r, e, scaled_max_m;
	unsigned long scaled_rt_rp, new_rate;
	int min_e = -1, min_e_m = -1, min_e_n = -1;
	struct dpll_data *dd;

	if (!clk || !clk->dpll_data)
		return ~0;

	dd = clk->dpll_data;

	pr_debug("clock: starting DPLL round_rate for clock %s, target rate "
		 "%ld\n", clk->name, target_rate);

	scaled_rt_rp = target_rate / (dd->clk_ref->rate / DPLL_SCALE_FACTOR);
	scaled_max_m = dd->max_multiplier * DPLL_SCALE_FACTOR;

	dd->last_rounded_rate = 0;

	for (n = dd->min_divider; n <= dd->max_divider; n++) {

		/* Is the (input clk, divider) pair valid for the DPLL? */
		r = _dpll_test_fint(clk, n);
		if (r == DPLL_FINT_UNDERFLOW)
			break;
		else if (r == DPLL_FINT_INVALID)
			continue;

		/* Compute the scaled DPLL multiplier, based on the divider */
		m = scaled_rt_rp * n;

		/*
		 * Since we're counting n up, a m overflow means we
		 * can bail out completely (since as n increases in
		 * the next iteration, there's no way that m can
		 * increase beyond the current m)
		 */
		if (m > scaled_max_m)
			break;

		r = _dpll_test_mult(&m, n, &new_rate, target_rate,
				    dd->clk_ref->rate);

		/* m can't be set low enough for this n - try with a larger n */
		if (r == DPLL_MULT_UNDERFLOW)
			continue;

		e = target_rate - new_rate;
		pr_debug("clock: n = %d: m = %d: rate error is %d "
			 "(new_rate = %ld)\n", n, m, e, new_rate);

		if (min_e == -1 ||
		    min_e >= (int)(abs(e) - dd->rate_tolerance)) {
			min_e = e;
			min_e_m = m;
			min_e_n = n;

			pr_debug("clock: found new least error %d\n", min_e);

			/* We found good settings -- bail out now */
			if (min_e <= dd->rate_tolerance)
				break;
		}
	}

	if (min_e < 0) {
		pr_debug("clock: error: target rate or tolerance too low\n");
		return ~0;
	}

	dd->last_rounded_m = min_e_m;
	dd->last_rounded_n = min_e_n;
	dd->last_rounded_rate = _dpll_compute_new_rate(dd->clk_ref->rate,
						       min_e_m,  min_e_n);

	pr_debug("clock: final least error: e = %d, m = %d, n = %d\n",
		 min_e, min_e_m, min_e_n);
	pr_debug("clock: final rate: %ld  (target rate: %ld)\n",
		 dd->last_rounded_rate, target_rate);

	return dd->last_rounded_rate;
}