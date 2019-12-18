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
struct se_device {int /*<<< orphan*/  execute_task_lock; int /*<<< orphan*/  state_list; } ;
struct se_cmd {int state_active; int /*<<< orphan*/  state_list; struct se_device* se_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void target_add_to_state_list(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->execute_task_lock, flags);
	if (!cmd->state_active) {
		list_add_tail(&cmd->state_list, &dev->state_list);
		cmd->state_active = true;
	}
	spin_unlock_irqrestore(&dev->execute_task_lock, flags);
}