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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct lbs_private {int (* hw_host_to_card ) (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ;int /*<<< orphan*/  command_timer; int /*<<< orphan*/  driver_lock; scalar_t__ cur_cmd_retcode; struct cmd_ctrl_node* cur_cmd; } ;
struct cmd_header {int /*<<< orphan*/  seqnum; int /*<<< orphan*/  command; int /*<<< orphan*/  size; } ;
struct cmd_ctrl_node {struct cmd_header* cmdbuf; } ;

/* Variables and functions */
 scalar_t__ CMD_802_11_ASSOCIATE ; 
 scalar_t__ CMD_802_11_SCAN ; 
 int HZ ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 int /*<<< orphan*/  LBS_DEB_HOST ; 
 int /*<<< orphan*/  MVMS_CMD ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,void*,scalar_t__) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_pr_info (char*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void lbs_submit_command(struct lbs_private *priv,
			       struct cmd_ctrl_node *cmdnode)
{
	unsigned long flags;
	struct cmd_header *cmd;
	uint16_t cmdsize;
	uint16_t command;
	int timeo = 3 * HZ;
	int ret;

	lbs_deb_enter(LBS_DEB_HOST);

	cmd = cmdnode->cmdbuf;

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->cur_cmd = cmdnode;
	priv->cur_cmd_retcode = 0;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	cmdsize = le16_to_cpu(cmd->size);
	command = le16_to_cpu(cmd->command);

	/* These commands take longer */
	if (command == CMD_802_11_SCAN || command == CMD_802_11_ASSOCIATE)
		timeo = 5 * HZ;

	lbs_deb_cmd("DNLD_CMD: command 0x%04x, seq %d, size %d\n",
		     command, le16_to_cpu(cmd->seqnum), cmdsize);
	lbs_deb_hex(LBS_DEB_CMD, "DNLD_CMD", (void *) cmdnode->cmdbuf, cmdsize);

	ret = priv->hw_host_to_card(priv, MVMS_CMD, (u8 *) cmd, cmdsize);

	if (ret) {
		lbs_pr_info("DNLD_CMD: hw_host_to_card failed: %d\n", ret);
		/* Let the timer kick in and retry, and potentially reset
		   the whole thing if the condition persists */
		timeo = HZ/4;
	}

	/* Setup the timer after transmit command */
	mod_timer(&priv->command_timer, jiffies + timeo);

	lbs_deb_leave(LBS_DEB_HOST);
}