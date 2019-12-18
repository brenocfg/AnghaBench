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
typedef  int u32 ;
struct clk {int clksel_mask; int /*<<< orphan*/  clksel_reg; } ;

/* Variables and functions */
 int __ffs (int) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int omap2_clksel_to_divisor (struct clk*,int) ; 

u32 omap2_clksel_get_divisor(struct clk *clk)
{
	u32 v;

	if (!clk->clksel_mask)
		return 0;

	v = __raw_readl(clk->clksel_reg) & clk->clksel_mask;
	v >>= __ffs(clk->clksel_mask);

	return omap2_clksel_to_divisor(clk, v);
}