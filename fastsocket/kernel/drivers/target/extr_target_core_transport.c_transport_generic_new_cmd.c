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
struct se_cmd {int se_cmd_flags; scalar_t__ data_direction; int /*<<< orphan*/  se_dev; int /*<<< orphan*/  t_state; TYPE_1__* se_tfo; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  t_fe_count; scalar_t__ data_length; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_2__ {int (* write_pending ) (struct se_cmd*) ;} ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  TRANSPORT_COMPLETE_QF_WP ; 
 int /*<<< orphan*/  TRANSPORT_WRITE_PENDING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct se_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  target_add_to_state_list (struct se_cmd*) ; 
 int /*<<< orphan*/  target_execute_cmd (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_cmd_check_stop (struct se_cmd*,int) ; 
 int transport_generic_get_mem (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_handle_queue_full (struct se_cmd*,int /*<<< orphan*/ ) ; 

sense_reason_t
transport_generic_new_cmd(struct se_cmd *cmd)
{
	int ret = 0;

	/*
	 * Determine is the TCM fabric module has already allocated physical
	 * memory, and is directly calling transport_generic_map_mem_to_cmd()
	 * beforehand.
	 */
	if (!(cmd->se_cmd_flags & SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC) &&
	    cmd->data_length) {
		ret = transport_generic_get_mem(cmd);
		if (ret < 0)
			return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	atomic_inc(&cmd->t_fe_count);

	/*
	 * If this command is not a write we can execute it right here,
	 * for write buffers we need to notify the fabric driver first
	 * and let it call back once the write buffers are ready.
	 */
	target_add_to_state_list(cmd);
	if (cmd->data_direction != DMA_TO_DEVICE) {
		target_execute_cmd(cmd);
		return 0;
	}

	spin_lock_irq(&cmd->t_state_lock);
	cmd->t_state = TRANSPORT_WRITE_PENDING;
	spin_unlock_irq(&cmd->t_state_lock);

	transport_cmd_check_stop(cmd, false);

	ret = cmd->se_tfo->write_pending(cmd);
	if (ret == -EAGAIN || ret == -ENOMEM)
		goto queue_full;

	/* fabric drivers should only return -EAGAIN or -ENOMEM as error */
	WARN_ON(ret);

	return (!ret) ? 0 : TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

queue_full:
	pr_debug("Handling write_pending QUEUE__FULL: se_cmd: %p\n", cmd);
	cmd->t_state = TRANSPORT_COMPLETE_QF_WP;
	transport_handle_queue_full(cmd, cmd->se_dev);
	return 0;
}