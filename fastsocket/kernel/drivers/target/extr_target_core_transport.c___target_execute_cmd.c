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
struct se_cmd {int transport_state; int /*<<< orphan*/  t_state_lock; scalar_t__ (* execute_cmd ) (struct se_cmd*) ;} ;
typedef  scalar_t__ sense_reason_t ;

/* Variables and functions */
 int CMD_T_BUSY ; 
 int CMD_T_SENT ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_generic_request_failure (struct se_cmd*,scalar_t__) ; 

__attribute__((used)) static void __target_execute_cmd(struct se_cmd *cmd)
{
	sense_reason_t ret;

	spin_lock_irq(&cmd->t_state_lock);
	cmd->transport_state |= (CMD_T_BUSY|CMD_T_SENT);
	spin_unlock_irq(&cmd->t_state_lock);

	if (cmd->execute_cmd) {
		ret = cmd->execute_cmd(cmd);
		if (ret) {
			spin_lock_irq(&cmd->t_state_lock);
			cmd->transport_state &= ~(CMD_T_BUSY|CMD_T_SENT);
			spin_unlock_irq(&cmd->t_state_lock);

			transport_generic_request_failure(cmd, ret);
		}
	}
}