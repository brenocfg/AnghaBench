#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct clk {TYPE_1__* parent; } ;
struct TYPE_3__ {unsigned long (* get_rate ) (TYPE_1__*) ;} ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 long EINVAL ; 
 int /*<<< orphan*/  PLLCOUNT ; 
 int /*<<< orphan*/  PLLDIV ; 
 int /*<<< orphan*/  PLLMUL ; 
 int /*<<< orphan*/  PLLOPT ; 
 int /*<<< orphan*/  PLLOSC ; 
 int /*<<< orphan*/  PM_BF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PM_BIT (int /*<<< orphan*/ ) ; 
 unsigned long abs (unsigned long) ; 
 TYPE_1__ osc1 ; 
 unsigned long stub1 (TYPE_1__*) ; 

__attribute__((used)) static long pll_set_rate(struct clk *clk, unsigned long rate,
			 u32 *pll_ctrl)
{
	unsigned long mul;
	unsigned long mul_best_fit = 0;
	unsigned long div;
	unsigned long div_min;
	unsigned long div_max;
	unsigned long div_best_fit = 0;
	unsigned long base;
	unsigned long pll_in;
	unsigned long actual = 0;
	unsigned long rate_error;
	unsigned long rate_error_prev = ~0UL;
	u32 ctrl;

	/* Rate must be between 80 MHz and 200 Mhz. */
	if (rate < 80000000UL || rate > 200000000UL)
		return -EINVAL;

	ctrl = PM_BF(PLLOPT, 4);
	base = clk->parent->get_rate(clk->parent);

	/* PLL input frequency must be between 6 MHz and 32 MHz. */
	div_min = DIV_ROUND_UP(base, 32000000UL);
	div_max = base / 6000000UL;

	if (div_max < div_min)
		return -EINVAL;

	for (div = div_min; div <= div_max; div++) {
		pll_in = (base + div / 2) / div;
		mul = (rate + pll_in / 2) / pll_in;

		if (mul == 0)
			continue;

		actual = pll_in * mul;
		rate_error = abs(actual - rate);

		if (rate_error < rate_error_prev) {
			mul_best_fit = mul;
			div_best_fit = div;
			rate_error_prev = rate_error;
		}

		if (rate_error == 0)
			break;
	}

	if (div_best_fit == 0)
		return -EINVAL;

	ctrl |= PM_BF(PLLMUL, mul_best_fit - 1);
	ctrl |= PM_BF(PLLDIV, div_best_fit - 1);
	ctrl |= PM_BF(PLLCOUNT, 16);

	if (clk->parent == &osc1)
		ctrl |= PM_BIT(PLLOSC);

	*pll_ctrl = ctrl;

	return actual;
}