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
struct se_cmd {int se_cmd_flags; scalar_t__ data_direction; TYPE_1__* se_tfo; int /*<<< orphan*/ * t_task_cdb; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  transport_state; int /*<<< orphan*/  t_state_lock; } ;
struct TYPE_2__ {scalar_t__ (* write_pending_status ) (struct se_cmd*) ;int /*<<< orphan*/  (* queue_status ) (struct se_cmd*) ;int /*<<< orphan*/  (* get_task_tag ) (struct se_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_T_ABORTED ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SAM_STAT_TASK_ABORTED ; 
 int SCF_SENT_CHECK_CONDITION ; 
 int SCF_SENT_DELAYED_TAS ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic_inc () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub2 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub3 (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_lun_remove_cmd (struct se_cmd*) ; 

void transport_send_task_abort(struct se_cmd *cmd)
{
	unsigned long flags;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	if (cmd->se_cmd_flags & (SCF_SENT_CHECK_CONDITION | SCF_SENT_DELAYED_TAS)) {
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	/*
	 * If there are still expected incoming fabric WRITEs, we wait
	 * until until they have completed before sending a TASK_ABORTED
	 * response.  This response with TASK_ABORTED status will be
	 * queued back to fabric module by transport_check_aborted_status().
	 */
	if (cmd->data_direction == DMA_TO_DEVICE) {
		if (cmd->se_tfo->write_pending_status(cmd) != 0) {
			cmd->transport_state |= CMD_T_ABORTED;
			smp_mb__after_atomic_inc();
		}
	}
	cmd->scsi_status = SAM_STAT_TASK_ABORTED;

	transport_lun_remove_cmd(cmd);

	pr_debug("Setting SAM_STAT_TASK_ABORTED status for CDB: 0x%02x,"
		" ITT: 0x%08x\n", cmd->t_task_cdb[0],
		cmd->se_tfo->get_task_tag(cmd));

	cmd->se_tfo->queue_status(cmd);
}