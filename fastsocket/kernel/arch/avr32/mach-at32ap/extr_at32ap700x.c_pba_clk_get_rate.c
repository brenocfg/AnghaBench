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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CKSEL ; 
 int /*<<< orphan*/  PBADIV ; 
 int /*<<< orphan*/  PBASEL ; 
 int PM_BFEXT (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long PM_BIT (int /*<<< orphan*/ ) ; 
 unsigned long bus_clk_get_rate (struct clk*,unsigned long) ; 
 unsigned long pm_readl (int /*<<< orphan*/ ) ; 

unsigned long pba_clk_get_rate(struct clk *clk)
{
	unsigned long cksel, shift = 0;

	cksel = pm_readl(CKSEL);
	if (cksel & PM_BIT(PBADIV))
		shift = PM_BFEXT(PBASEL, cksel) + 1;

	return bus_clk_get_rate(clk, shift);
}