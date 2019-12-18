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
struct clk {struct clk* parent; scalar_t__ usage; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_parent ) (struct clk*,struct clk*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  clk_good (struct clk*) ; 
 int /*<<< orphan*/  clocks_lock ; 
 int /*<<< orphan*/  local_clk_disable (struct clk*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct clk*,struct clk*) ; 
 scalar_t__ unlikely (int) ; 

int clk_set_parent(struct clk *clk, struct clk *parent)
{
	int ret = -ENODEV;
	unsigned long clocks_flags;

	if (unlikely(!clk_good(clk)))
		goto out;

	if (!clk->ops->set_parent)
		goto out;

	spin_lock_irqsave(&clocks_lock, clocks_flags);

	ret = clk->ops->set_parent(clk, parent);
	if (!ret) {
		/* disable if usage count is 0 */
		local_clk_disable(parent);

		parent->usage += clk->usage;
		clk->parent->usage -= clk->usage;

		/* disable if new usage count is 0 */
		local_clk_disable(clk->parent);

		clk->parent = parent;
	}
	spin_unlock_irqrestore(&clocks_lock, clocks_flags);

out:
	return ret;
}