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
typedef  int /*<<< orphan*/  uint16_t ;
struct lbtf_private {int /*<<< orphan*/  driver_lock; } ;
struct cmd_header {int dummy; } ;
struct cmd_ctrl_node {int result; int /*<<< orphan*/  cmdwaitqwoken; int /*<<< orphan*/  cmdwait_q; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  LBTF_DEB_HOST ; 
 int PTR_ERR (struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  __lbtf_cleanup_and_insert_cmd (struct lbtf_private*,struct cmd_ctrl_node*) ; 
 struct cmd_ctrl_node* __lbtf_cmd_async (struct lbtf_private*,int /*<<< orphan*/ ,struct cmd_header*,int,int (*) (struct lbtf_private*,unsigned long,struct cmd_header*),unsigned long) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __lbtf_cmd(struct lbtf_private *priv, uint16_t command,
	      struct cmd_header *in_cmd, int in_cmd_size,
	      int (*callback)(struct lbtf_private *,
			      unsigned long, struct cmd_header *),
	      unsigned long callback_arg)
{
	struct cmd_ctrl_node *cmdnode;
	unsigned long flags;
	int ret = 0;

	lbtf_deb_enter(LBTF_DEB_HOST);

	cmdnode = __lbtf_cmd_async(priv, command, in_cmd, in_cmd_size,
				  callback, callback_arg);
	if (IS_ERR(cmdnode)) {
		ret = PTR_ERR(cmdnode);
		goto done;
	}

	might_sleep();
	ret = wait_event_interruptible(cmdnode->cmdwait_q,
				       cmdnode->cmdwaitqwoken);
	if (ret) {
		pr_info("PREP_CMD: command 0x%04x interrupted by signal: %d\n",
			    command, ret);
		goto done;
	}

	spin_lock_irqsave(&priv->driver_lock, flags);
	ret = cmdnode->result;
	if (ret)
		pr_info("PREP_CMD: command 0x%04x failed: %d\n",
			    command, ret);

	__lbtf_cleanup_and_insert_cmd(priv, cmdnode);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

done:
	lbtf_deb_leave_args(LBTF_DEB_HOST, "ret %d", ret);
	return ret;
}