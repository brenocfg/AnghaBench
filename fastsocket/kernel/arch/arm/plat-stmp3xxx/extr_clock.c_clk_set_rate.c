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
struct clk {int flags; unsigned long rate; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_rate ) (struct clk*,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int FIXED_RATE ; 
 int RATE_PROPAGATES ; 
 int /*<<< orphan*/  clk_good (struct clk*) ; 
 int /*<<< orphan*/  close_enough (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  propagate_rate (struct clk*) ; 
 int stub1 (struct clk*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	int ret = -EINVAL;

	if (unlikely(!clk_good(clk)))
		goto out;

	if (clk->flags & FIXED_RATE || !clk->ops->set_rate)
		goto out;

	else if (!close_enough(clk->rate, rate)) {
		ret = clk->ops->set_rate(clk, rate);
		if (ret < 0)
			goto out;
		clk->rate = rate;
		if (clk->flags & RATE_PROPAGATES)
			propagate_rate(clk);
	} else
		ret = 0;

out:
	return ret;
}