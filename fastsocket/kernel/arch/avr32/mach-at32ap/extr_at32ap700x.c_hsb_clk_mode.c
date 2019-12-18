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
 int /*<<< orphan*/  HSB_MASK ; 
 int /*<<< orphan*/  pm_lock ; 
 int pm_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hsb_clk_mode(struct clk *clk, int enabled)
{
	unsigned long flags;
	u32 mask;

	spin_lock_irqsave(&pm_lock, flags);
	mask = pm_readl(HSB_MASK);
	if (enabled)
		mask |= 1 << clk->index;
	else
		mask &= ~(1 << clk->index);
	pm_writel(HSB_MASK, mask);
	spin_unlock_irqrestore(&pm_lock, flags);
}