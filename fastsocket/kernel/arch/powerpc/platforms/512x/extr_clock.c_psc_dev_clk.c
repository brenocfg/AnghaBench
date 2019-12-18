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
struct clk {int bit; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 struct clk** dev_clks ; 

__attribute__((used)) static struct clk *psc_dev_clk(int pscnum)
{
	int reg, bit;
	struct clk *clk;

	reg = 0;
	bit = 27 - pscnum;

	clk = &dev_clks[reg][bit];
	clk->reg = 0;
	clk->bit = bit;
	return clk;
}