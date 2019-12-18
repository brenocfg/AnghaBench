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
struct se_cmd {int transport_state; int se_cmd_flags; TYPE_1__* se_tfo; int /*<<< orphan*/ * t_task_cdb; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* queue_status ) (struct se_cmd*) ;int /*<<< orphan*/  (* get_task_tag ) (struct se_cmd*) ;} ;

/* Variables and functions */
 int CMD_T_ABORTED ; 
 int SCF_SENT_DELAYED_TAS ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub2 (struct se_cmd*) ; 

int transport_check_aborted_status(struct se_cmd *cmd, int send_status)
{
	if (!(cmd->transport_state & CMD_T_ABORTED))
		return 0;

	if (!send_status || (cmd->se_cmd_flags & SCF_SENT_DELAYED_TAS))
		return 1;

	pr_debug("Sending delayed SAM_STAT_TASK_ABORTED status for CDB: 0x%02x ITT: 0x%08x\n",
		 cmd->t_task_cdb[0], cmd->se_tfo->get_task_tag(cmd));

	cmd->se_cmd_flags |= SCF_SENT_DELAYED_TAS;
	cmd->se_tfo->queue_status(cmd);

	return 1;
}