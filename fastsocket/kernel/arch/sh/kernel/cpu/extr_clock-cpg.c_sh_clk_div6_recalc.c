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
struct clk_div_mult_table {int /*<<< orphan*/  nr_divisors; } ;
struct clk {TYPE_1__* freq_table; int /*<<< orphan*/  enable_reg; } ;
struct TYPE_2__ {unsigned long frequency; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_rate_table_build (struct clk*,TYPE_1__*,int /*<<< orphan*/ ,struct clk_div_mult_table*,int /*<<< orphan*/ *) ; 
 struct clk_div_mult_table sh_clk_div6_table ; 

__attribute__((used)) static unsigned long sh_clk_div6_recalc(struct clk *clk)
{
	struct clk_div_mult_table *table = &sh_clk_div6_table;
	unsigned int idx;

	clk_rate_table_build(clk, clk->freq_table, table->nr_divisors,
			     table, NULL);

	idx = __raw_readl(clk->enable_reg) & 0x003f;

	return clk->freq_table[idx].frequency;
}