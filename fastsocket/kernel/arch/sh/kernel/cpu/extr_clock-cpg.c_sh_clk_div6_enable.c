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
struct clk {int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int sh_clk_div6_set_rate (struct clk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_clk_div6_enable(struct clk *clk)
{
	unsigned long value;
	int ret;

	ret = sh_clk_div6_set_rate(clk, clk->rate, 0);
	if (ret == 0) {
		value = __raw_readl(clk->enable_reg);
		value &= ~0x100; /* clear stop bit to enable clock */
		__raw_writel(value, clk->enable_reg);
	}
	return ret;
}