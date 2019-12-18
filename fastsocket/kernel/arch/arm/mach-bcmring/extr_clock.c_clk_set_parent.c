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
struct clk {int use_cnt; int /*<<< orphan*/  mode; struct clk* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_MODE_XTAL ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  __clk_disable (struct clk*) ; 
 int /*<<< orphan*/  __clk_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_is_bypassable (struct clk*) ; 
 int /*<<< orphan*/  clk_is_primary (struct clk*) ; 
 scalar_t__ clk_is_using_xtal (struct clk*) ; 
 int /*<<< orphan*/  clk_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int clk_set_parent(struct clk *clk, struct clk *parent)
{
	unsigned long flags;
	struct clk *old_parent;

	if (!clk || !parent)
		return -EINVAL;

	if (!clk_is_primary(parent) || !clk_is_bypassable(clk))
		return -EINVAL;

	/* if more than one user, parent is not allowed */
	if (clk->use_cnt > 1)
		return -EBUSY;

	if (clk->parent == parent)
		return 0;

	spin_lock_irqsave(&clk_lock, flags);
	old_parent = clk->parent;
	clk->parent = parent;
	if (clk_is_using_xtal(parent))
		clk->mode |= CLK_MODE_XTAL;
	else
		clk->mode &= (~CLK_MODE_XTAL);

	/* if clock is active */
	if (clk->use_cnt != 0) {
		clk->use_cnt--;
		/* enable clock with the new parent */
		__clk_enable(clk);
		/* disable the old parent */
		__clk_disable(old_parent);
	}
	spin_unlock_irqrestore(&clk_lock, flags);

	return 0;
}