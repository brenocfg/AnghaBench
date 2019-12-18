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
struct clk {scalar_t__ usage; struct clk* parent; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct clk*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_good (struct clk*) ; 
 int /*<<< orphan*/  clocks_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct clk*) ; 
 scalar_t__ unlikely (int) ; 

void clk_disable(struct clk *clk)
{
	unsigned long clocks_flags;

	if (unlikely(!clk_good(clk)))
		return;

	spin_lock_irqsave(&clocks_lock, clocks_flags);

	if ((--clk->usage) == 0 && clk->ops->disable)
		clk->ops->disable(clk);

	spin_unlock_irqrestore(&clocks_lock, clocks_flags);
	if (clk->parent)
		clk_disable(clk->parent);
}