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
typedef  scalar_t__ u32 ;
struct clk {scalar_t__ rate; } ;

/* Variables and functions */
 scalar_t__ CLK_RATE_13MHZ ; 
 int /*<<< orphan*/  clk_reg_disable (struct clk*) ; 
 int /*<<< orphan*/  clk_reg_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_wait_for_pll_lock (struct clk*) ; 

__attribute__((used)) static int pll1_set_rate(struct clk *clk, u32 rate)
{
#if 0 /* doesn't work on some boards, probably a HW BUG */
	if (rate) {
		clk_reg_disable(clk);	/*enable bit is inverted */
		if (!clk_wait_for_pll_lock(clk)) {
			clk->rate = CLK_RATE_13MHZ;
		} else {
			clk_reg_enable(clk);
			clk->rate = 0;
		}

	} else {
		clk_reg_enable(clk);
		clk->rate = 0;
	}
#endif
	return 0;
}