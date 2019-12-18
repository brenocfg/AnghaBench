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
struct se_lun {int dummy; } ;
struct se_cmd {int transport_state; TYPE_1__* se_tfo; int /*<<< orphan*/  transport_lun_stop_comp; int /*<<< orphan*/  t_state_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_task_tag ) (struct se_cmd*) ;} ;

/* Variables and functions */
 int CMD_T_BUSY ; 
 int CMD_T_LUN_FE_STOP ; 
 int CMD_T_LUN_STOP ; 
 int CMD_T_SENT ; 
 int CMD_T_STOP ; 
 int EPERM ; 
 int /*<<< orphan*/  pr_debug (char*,struct se_cmd*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub2 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub3 (struct se_cmd*) ; 
 int /*<<< orphan*/  target_stop_cmd (struct se_cmd*,unsigned long*) ; 
 int /*<<< orphan*/  transport_cmd_check_stop (struct se_cmd*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int transport_lun_wait_for_tasks(struct se_cmd *cmd, struct se_lun *lun)
{
	unsigned long flags;
	int ret = 0;

	/*
	 * If the frontend has already requested this struct se_cmd to
	 * be stopped, we can safely ignore this struct se_cmd.
	 */
	spin_lock_irqsave(&cmd->t_state_lock, flags);
	if (cmd->transport_state & CMD_T_STOP) {
		cmd->transport_state &= ~CMD_T_LUN_STOP;

		pr_debug("ConfigFS ITT[0x%08x] - CMD_T_STOP, skipping\n",
			 cmd->se_tfo->get_task_tag(cmd));
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		transport_cmd_check_stop(cmd, false);
		return -EPERM;
	}
	cmd->transport_state |= CMD_T_LUN_FE_STOP;
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	// XXX: audit task_flags checks.
	spin_lock_irqsave(&cmd->t_state_lock, flags);
	if ((cmd->transport_state & CMD_T_BUSY) &&
	    (cmd->transport_state & CMD_T_SENT)) {
		if (!target_stop_cmd(cmd, &flags))
			ret++;
	}
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	pr_debug("ConfigFS: cmd: %p stop tasks ret:"
			" %d\n", cmd, ret);
	if (!ret) {
		pr_debug("ConfigFS: ITT[0x%08x] - stopping cmd....\n",
				cmd->se_tfo->get_task_tag(cmd));
		wait_for_completion(&cmd->transport_lun_stop_comp);
		pr_debug("ConfigFS: ITT[0x%08x] - stopped cmd....\n",
				cmd->se_tfo->get_task_tag(cmd));
	}

	return 0;
}