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
typedef  int uint16_t ;
struct lbtf_private {int seqnum; int /*<<< orphan*/  cmd_work; scalar_t__ surpriseremoved; } ;
struct cmd_header {int dummy; } ;
struct cmd_ctrl_node {int (* callback ) (struct lbtf_private*,unsigned long,struct cmd_header*) ;unsigned long callback_arg; scalar_t__ cmdwaitqwoken; TYPE_1__* cmdbuf; } ;
struct TYPE_2__ {scalar_t__ result; void* seqnum; void* size; void* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  ENOENT ; 
 struct cmd_ctrl_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LBTF_DEB_HOST ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_host (char*,...) ; 
 int /*<<< orphan*/  lbtf_deb_leave_args (int /*<<< orphan*/ ,char*,struct cmd_ctrl_node*) ; 
 struct cmd_ctrl_node* lbtf_get_cmd_ctrl_node (struct lbtf_private*) ; 
 int /*<<< orphan*/  lbtf_queue_cmd (struct lbtf_private*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  lbtf_wq ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct cmd_header*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cmd_ctrl_node *__lbtf_cmd_async(struct lbtf_private *priv,
	uint16_t command, struct cmd_header *in_cmd, int in_cmd_size,
	int (*callback)(struct lbtf_private *, unsigned long,
			struct cmd_header *),
	unsigned long callback_arg)
{
	struct cmd_ctrl_node *cmdnode;

	lbtf_deb_enter(LBTF_DEB_HOST);

	if (priv->surpriseremoved) {
		lbtf_deb_host("PREP_CMD: card removed\n");
		cmdnode = ERR_PTR(-ENOENT);
		goto done;
	}

	cmdnode = lbtf_get_cmd_ctrl_node(priv);
	if (cmdnode == NULL) {
		lbtf_deb_host("PREP_CMD: cmdnode is NULL\n");

		/* Wake up main thread to execute next command */
		queue_work(lbtf_wq, &priv->cmd_work);
		cmdnode = ERR_PTR(-ENOBUFS);
		goto done;
	}

	cmdnode->callback = callback;
	cmdnode->callback_arg = callback_arg;

	/* Copy the incoming command to the buffer */
	memcpy(cmdnode->cmdbuf, in_cmd, in_cmd_size);

	/* Set sequence number, clean result, move to buffer */
	priv->seqnum++;
	cmdnode->cmdbuf->command = cpu_to_le16(command);
	cmdnode->cmdbuf->size    = cpu_to_le16(in_cmd_size);
	cmdnode->cmdbuf->seqnum  = cpu_to_le16(priv->seqnum);
	cmdnode->cmdbuf->result  = 0;

	lbtf_deb_host("PREP_CMD: command 0x%04x\n", command);

	cmdnode->cmdwaitqwoken = 0;
	lbtf_queue_cmd(priv, cmdnode);
	queue_work(lbtf_wq, &priv->cmd_work);

 done:
	lbtf_deb_leave_args(LBTF_DEB_HOST, "ret %p", cmdnode);
	return cmdnode;
}