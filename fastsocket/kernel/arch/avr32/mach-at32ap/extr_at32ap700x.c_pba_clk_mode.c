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
struct clk {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBA_MASK ; 
 int /*<<< orphan*/  pm_lock ; 
 int pm_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pba_clk_mode(struct clk *clk, int enabled)
{
	unsigned long flags;
	u32 mask;

	spin_lock_irqsave(&pm_lock, flags);
	mask = pm_readl(PBA_MASK);
	if (enabled)
		mask |= 1 << clk->index;
	else
		mask &= ~(1 << clk->index);
	pm_writel(PBA_MASK, mask);
	spin_unlock_irqrestore(&pm_lock, flags);
}