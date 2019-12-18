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
struct clk {int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  freq_table; } ;

/* Variables and functions */
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int clk_rate_table_find (struct clk*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int sh_clk_div6_set_rate(struct clk *clk,
				unsigned long rate, int algo_id)
{
	unsigned long value;
	int idx;

	idx = clk_rate_table_find(clk, clk->freq_table, rate);
	if (idx < 0)
		return idx;

	value = __raw_readl(clk->enable_reg);
	value &= ~0x3f;
	value |= idx;
	__raw_writel(value, clk->enable_reg);
	return 0;
}