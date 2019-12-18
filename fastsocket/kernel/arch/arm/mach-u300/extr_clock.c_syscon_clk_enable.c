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
struct clk {int /*<<< orphan*/  clk_val; scalar_t__ hw_ctrld; } ;

/* Variables and functions */
 scalar_t__ U300_SYSCON_SBCER ; 
 scalar_t__ U300_SYSCON_VBASE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  syscon_clkreg_lock ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void syscon_clk_enable(struct clk *clk)
{
	unsigned long iflags;

	/* Don't touch the hardware controlled clocks */
	if (clk->hw_ctrld)
		return;

	spin_lock_irqsave(&syscon_clkreg_lock, iflags);
	writew(clk->clk_val, U300_SYSCON_VBASE + U300_SYSCON_SBCER);
	spin_unlock_irqrestore(&syscon_clkreg_lock, iflags);
}