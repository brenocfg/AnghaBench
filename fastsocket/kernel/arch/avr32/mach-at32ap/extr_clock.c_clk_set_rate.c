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
struct clk {long (* set_rate ) (struct clk*,unsigned long,int) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  clk_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 long stub1 (struct clk*,unsigned long,int) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	unsigned long flags;
	long ret;

	if (!clk->set_rate)
		return -ENOSYS;

	spin_lock_irqsave(&clk_lock, flags);
	ret = clk->set_rate(clk, rate, 1);
	spin_unlock_irqrestore(&clk_lock, flags);

	return (ret < 0) ? ret : 0;
}