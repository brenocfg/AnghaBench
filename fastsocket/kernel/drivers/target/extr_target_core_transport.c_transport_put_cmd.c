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
struct se_cmd {int transport_state; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  t_fe_count; } ;

/* Variables and functions */
 int CMD_T_DEV_ACTIVE ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  target_remove_from_state_list (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_free_pages (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_release_cmd (struct se_cmd*) ; 

__attribute__((used)) static void transport_put_cmd(struct se_cmd *cmd)
{
	unsigned long flags;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	if (atomic_read(&cmd->t_fe_count) &&
	    !atomic_dec_and_test(&cmd->t_fe_count)) {
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		return;
	}

	if (cmd->transport_state & CMD_T_DEV_ACTIVE) {
		cmd->transport_state &= ~CMD_T_DEV_ACTIVE;
		target_remove_from_state_list(cmd);
	}
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	transport_free_pages(cmd);
	transport_release_cmd(cmd);
	return;
}