#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lbs_private {int cmd_timed_out; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  waitq; TYPE_2__* cur_cmd; } ;
struct TYPE_4__ {TYPE_1__* cmdbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void command_timer_fn(unsigned long data)
{
	struct lbs_private *priv = (struct lbs_private *)data;
	unsigned long flags;

	lbs_deb_enter(LBS_DEB_CMD);
	spin_lock_irqsave(&priv->driver_lock, flags);

	if (!priv->cur_cmd)
		goto out;

	lbs_pr_info("command 0x%04x timed out\n",
		le16_to_cpu(priv->cur_cmd->cmdbuf->command));

	priv->cmd_timed_out = 1;
	wake_up_interruptible(&priv->waitq);
out:
	spin_unlock_irqrestore(&priv->driver_lock, flags);
	lbs_deb_leave(LBS_DEB_CMD);
}