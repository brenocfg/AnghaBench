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
struct clk {scalar_t__ usecount; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; struct clk* parent; int /*<<< orphan*/  (* disable ) (struct clk*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  disable_i2s0_vcxo () ; 
 int /*<<< orphan*/  disable_i2s1_vcxo () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct clk*) ; 
 scalar_t__ unlikely (int) ; 

void clk_disable(struct clk *clk)
{
	unsigned long iflags;

	spin_lock_irqsave(&clk->lock, iflags);
	if (clk->usecount > 0 && !(--clk->usecount)) {
		/* some blocks lack clocking registers and cannot be disabled */
		if (clk->disable)
			clk->disable(clk);
		if (likely((u32)clk->parent))
			clk_disable(clk->parent);
	}
#ifdef CONFIG_MACH_U300_USE_I2S_AS_MASTER
	if (unlikely(!strcmp(clk->name, "I2S0")))
		disable_i2s0_vcxo();
	if (unlikely(!strcmp(clk->name, "I2S1")))
		disable_i2s1_vcxo();
#endif
	spin_unlock_irqrestore(&clk->lock, iflags);
}