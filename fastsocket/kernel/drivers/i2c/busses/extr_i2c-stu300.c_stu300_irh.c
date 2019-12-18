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
struct stu300_dev {scalar_t__ cmd_err; int /*<<< orphan*/  clk; int /*<<< orphan*/  cmd_issue_lock; int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  cmd_event; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ STU300_ERROR_NONE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stu300_event_occurred (struct stu300_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t stu300_irh(int irq, void *data)
{
	struct stu300_dev *dev = data;
	int res;

	/* Just make sure that the block is clocked */
	clk_enable(dev->clk);

	/* See if this was what we were waiting for */
	spin_lock(&dev->cmd_issue_lock);

	res = stu300_event_occurred(dev, dev->cmd_event);
	if (res || dev->cmd_err != STU300_ERROR_NONE)
		complete(&dev->cmd_complete);

	spin_unlock(&dev->cmd_issue_lock);

	clk_disable(dev->clk);

	return IRQ_HANDLED;
}