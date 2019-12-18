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
struct lbtf_private {int /*<<< orphan*/ * cur_cmd; } ;
struct cmd_ctrl_node {int result; int cmdwaitqwoken; int /*<<< orphan*/  callback; int /*<<< orphan*/  cmdwait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lbtf_cleanup_and_insert_cmd (struct lbtf_private*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void lbtf_complete_command(struct lbtf_private *priv, struct cmd_ctrl_node *cmd,
			  int result)
{
	cmd->result = result;
	cmd->cmdwaitqwoken = 1;
	wake_up_interruptible(&cmd->cmdwait_q);

	if (!cmd->callback)
		__lbtf_cleanup_and_insert_cmd(priv, cmd);
	priv->cur_cmd = NULL;
}