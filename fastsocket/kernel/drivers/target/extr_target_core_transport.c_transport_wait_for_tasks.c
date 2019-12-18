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
struct se_cmd {int se_cmd_flags; int transport_state; int /*<<< orphan*/  t_state_lock; TYPE_1__* se_tfo; int /*<<< orphan*/  t_transport_stop_comp; int /*<<< orphan*/  t_state; int /*<<< orphan*/  transport_lun_fe_stop_comp; int /*<<< orphan*/  transport_lun_stop_comp; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_task_tag ) (struct se_cmd*) ;int /*<<< orphan*/  (* get_cmd_state ) (struct se_cmd*) ;} ;

/* Variables and functions */
 int CMD_T_ACTIVE ; 
 int CMD_T_LUN_STOP ; 
 int CMD_T_STOP ; 
 int SCF_SCSI_TMR_CDB ; 
 int SCF_SE_LUN_CMD ; 
 int SCF_SUPPORTED_SAM_OPCODE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct se_cmd*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub2 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub3 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub4 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub5 (struct se_cmd*) ; 
 int /*<<< orphan*/  target_remove_from_state_list (struct se_cmd*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

bool transport_wait_for_tasks(struct se_cmd *cmd)
{
	unsigned long flags;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	if (!(cmd->se_cmd_flags & SCF_SE_LUN_CMD) &&
	    !(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)) {
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		return false;
	}

	if (!(cmd->se_cmd_flags & SCF_SUPPORTED_SAM_OPCODE) &&
	    !(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)) {
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		return false;
	}
	/*
	 * If we are already stopped due to an external event (ie: LUN shutdown)
	 * sleep until the connection can have the passed struct se_cmd back.
	 * The cmd->transport_lun_stopped_sem will be upped by
	 * transport_clear_lun_from_sessions() once the ConfigFS context caller
	 * has completed its operation on the struct se_cmd.
	 */
	if (cmd->transport_state & CMD_T_LUN_STOP) {
		pr_debug("wait_for_tasks: Stopping"
			" wait_for_completion(&cmd->t_tasktransport_lun_fe"
			"_stop_comp); for ITT: 0x%08x\n",
			cmd->se_tfo->get_task_tag(cmd));
		/*
		 * There is a special case for WRITES where a FE exception +
		 * LUN shutdown means ConfigFS context is still sleeping on
		 * transport_lun_stop_comp in transport_lun_wait_for_tasks().
		 * We go ahead and up transport_lun_stop_comp just to be sure
		 * here.
		 */
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		complete(&cmd->transport_lun_stop_comp);
		wait_for_completion(&cmd->transport_lun_fe_stop_comp);
		spin_lock_irqsave(&cmd->t_state_lock, flags);

		target_remove_from_state_list(cmd);
		/*
		 * At this point, the frontend who was the originator of this
		 * struct se_cmd, now owns the structure and can be released through
		 * normal means below.
		 */
		pr_debug("wait_for_tasks: Stopped"
			" wait_for_completion(&cmd->t_tasktransport_lun_fe_"
			"stop_comp); for ITT: 0x%08x\n",
			cmd->se_tfo->get_task_tag(cmd));

		cmd->transport_state &= ~CMD_T_LUN_STOP;
	}

	if (!(cmd->transport_state & CMD_T_ACTIVE)) {
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		return false;
	}

	cmd->transport_state |= CMD_T_STOP;

	pr_debug("wait_for_tasks: Stopping %p ITT: 0x%08x"
		" i_state: %d, t_state: %d, CMD_T_STOP\n",
		cmd, cmd->se_tfo->get_task_tag(cmd),
		cmd->se_tfo->get_cmd_state(cmd), cmd->t_state);

	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	wait_for_completion(&cmd->t_transport_stop_comp);

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	cmd->transport_state &= ~(CMD_T_ACTIVE | CMD_T_STOP);

	pr_debug("wait_for_tasks: Stopped wait_for_completion("
		"&cmd->t_transport_stop_comp) for ITT: 0x%08x\n",
		cmd->se_tfo->get_task_tag(cmd));

	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	return true;
}