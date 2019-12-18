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
typedef  int /*<<< orphan*/  u32 ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL1 ; 
 unsigned long pll_get_rate (struct clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long pll1_get_rate(struct clk *clk)
{
	u32 control;

	control = pm_readl(PLL1);

	return pll_get_rate(clk, control);
}