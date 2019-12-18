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
struct clk {unsigned long rate_hz; int /*<<< orphan*/  csp_id; TYPE_1__* parent; scalar_t__ use_cnt; } ;
struct TYPE_2__ {unsigned long rate_hz; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned long chipcHw_setClockFrequency (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clk_is_programmable (struct clk*) ; 
 int /*<<< orphan*/  clk_lock ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	unsigned long flags;
	unsigned long actual;
	unsigned long rate_hz;

	if (!clk)
		return -EINVAL;

	if (!clk_is_programmable(clk))
		return -EINVAL;

	if (clk->use_cnt)
		return -EBUSY;

	spin_lock_irqsave(&clk_lock, flags);
	actual = clk->parent->rate_hz;
	rate_hz = min(actual, rate);
	rate_hz = chipcHw_setClockFrequency(clk->csp_id, rate_hz);
	clk->rate_hz = rate_hz;
	spin_unlock_irqrestore(&clk_lock, flags);

	return 0;
}