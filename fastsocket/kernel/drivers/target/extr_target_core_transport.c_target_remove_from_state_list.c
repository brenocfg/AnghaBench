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
struct se_device {int /*<<< orphan*/  execute_task_lock; } ;
struct se_cmd {int transport_state; int state_active; int /*<<< orphan*/  state_list; struct se_device* se_dev; } ;

/* Variables and functions */
 int CMD_T_BUSY ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void target_remove_from_state_list(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	unsigned long flags;

	if (!dev)
		return;

	if (cmd->transport_state & CMD_T_BUSY)
		return;

	spin_lock_irqsave(&dev->execute_task_lock, flags);
	if (cmd->state_active) {
		list_del(&cmd->state_list);
		cmd->state_active = false;
	}
	spin_unlock_irqrestore(&dev->execute_task_lock, flags);
}