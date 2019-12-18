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
struct clksrc_clk {int divider_shift; int /*<<< orphan*/  reg_divider; } ;
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct clksrc_clk* to_clksrc (struct clk*) ; 

__attribute__((used)) static unsigned long s5pc1xx_getrate_clksrc(struct clk *clk)
{
	struct clksrc_clk *sclk = to_clksrc(clk);
	unsigned long rate = clk_get_rate(clk->parent);
	u32 clkdiv = __raw_readl(sclk->reg_divider);

	clkdiv >>= sclk->divider_shift;
	clkdiv &= 0xf;
	clkdiv++;

	rate /= clkdiv;
	return rate;
}