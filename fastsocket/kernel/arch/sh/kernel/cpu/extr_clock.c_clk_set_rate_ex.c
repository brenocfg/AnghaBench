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
struct clk {unsigned long rate; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_rate ) (struct clk*,unsigned long,int) ;unsigned long (* recalc ) (struct clk*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  clock_lock ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagate_rate (struct clk*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct clk*,unsigned long,int) ; 
 unsigned long stub2 (struct clk*) ; 

int clk_set_rate_ex(struct clk *clk, unsigned long rate, int algo_id)
{
	int ret = -EOPNOTSUPP;
	unsigned long flags;

	spin_lock_irqsave(&clock_lock, flags);

	if (likely(clk->ops && clk->ops->set_rate)) {
		ret = clk->ops->set_rate(clk, rate, algo_id);
		if (ret != 0)
			goto out_unlock;
	} else {
		clk->rate = rate;
		ret = 0;
	}

	if (clk->ops && clk->ops->recalc)
		clk->rate = clk->ops->recalc(clk);

	propagate_rate(clk);

out_unlock:
	spin_unlock_irqrestore(&clock_lock, flags);

	return ret;
}