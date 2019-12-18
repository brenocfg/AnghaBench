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
struct clk {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; int /*<<< orphan*/  (* enable ) (struct clk*) ;int /*<<< orphan*/  usecount; struct clk* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_i2s0_vcxo () ; 
 int /*<<< orphan*/  enable_i2s1_vcxo () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct clk*) ; 
 int /*<<< orphan*/  syscon_block_reset_disable (struct clk*) ; 
 scalar_t__ unlikely (int) ; 

int clk_enable(struct clk *clk)
{
	int ret = 0;
	unsigned long iflags;

	spin_lock_irqsave(&clk->lock, iflags);
	if (clk->usecount++ == 0) {
		if (likely((u32)clk->parent))
			ret = clk_enable(clk->parent);

		if (unlikely(ret != 0))
			clk->usecount--;
		else {
			/* remove reset line (we never enable reset again) */
			syscon_block_reset_disable(clk);
			/* clocks without enable function are always on */
			if (clk->enable)
				clk->enable(clk);
#ifdef CONFIG_MACH_U300_USE_I2S_AS_MASTER
			if (unlikely(!strcmp(clk->name, "I2S0")))
				enable_i2s0_vcxo();
			if (unlikely(!strcmp(clk->name, "I2S1")))
				enable_i2s1_vcxo();
#endif
		}
	}
	spin_unlock_irqrestore(&clk->lock, iflags);
	return ret;

}