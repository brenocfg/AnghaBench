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
struct se_lun {int /*<<< orphan*/  lun_cmd_lock; } ;
struct se_cmd {int transport_state; int /*<<< orphan*/  se_lun_node; int /*<<< orphan*/  t_state_lock; struct se_lun* se_lun; } ;

/* Variables and functions */
 int CMD_T_DEV_ACTIVE ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  target_remove_from_state_list (struct se_cmd*) ; 

__attribute__((used)) static void transport_lun_remove_cmd(struct se_cmd *cmd)
{
	struct se_lun *lun = cmd->se_lun;
	unsigned long flags;

	if (!lun)
		return;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	if (cmd->transport_state & CMD_T_DEV_ACTIVE) {
		cmd->transport_state &= ~CMD_T_DEV_ACTIVE;
		target_remove_from_state_list(cmd);
	}
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	spin_lock_irqsave(&lun->lun_cmd_lock, flags);
	if (!list_empty(&cmd->se_lun_node))
		list_del_init(&cmd->se_lun_node);
	spin_unlock_irqrestore(&lun->lun_cmd_lock, flags);
}