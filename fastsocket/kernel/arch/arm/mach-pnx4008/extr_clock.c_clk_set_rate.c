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
struct clk {int flags; int /*<<< orphan*/  (* round_rate ) (struct clk*,unsigned long) ;int /*<<< orphan*/  user_rate; scalar_t__ parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int FIXED_RATE ; 
 int PARENT_SET_RATE ; 
 int /*<<< orphan*/  clock_lock () ; 
 int /*<<< orphan*/  clock_unlock () ; 
 int local_set_rate (struct clk*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct clk*,unsigned long) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	int ret = -EINVAL;

	if (clk->flags & FIXED_RATE)
		goto out;

	clock_lock();
	if ((clk->flags & PARENT_SET_RATE) && clk->parent) {

		clk->user_rate = clk->round_rate(clk, rate);
		/* parent clock needs to be refreshed
		   for the setting to take effect */
	} else {
		ret = local_set_rate(clk, rate);
	}
	ret = 0;
	clock_unlock();

out:
	return ret;
}