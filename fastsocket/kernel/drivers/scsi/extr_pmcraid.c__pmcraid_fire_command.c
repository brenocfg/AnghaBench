#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmcraid_instance {int /*<<< orphan*/  ioarrin; int /*<<< orphan*/  outstanding_cmds; int /*<<< orphan*/  pending_pool_lock; int /*<<< orphan*/  pending_cmd_pool; } ;
struct pmcraid_cmd {TYPE_2__* ioa_cb; int /*<<< orphan*/  free_list; struct pmcraid_instance* drv_inst; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioarcb_bus_addr; } ;
struct TYPE_4__ {TYPE_1__ ioarcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void _pmcraid_fire_command(struct pmcraid_cmd *cmd)
{
	struct pmcraid_instance *pinstance = cmd->drv_inst;
	unsigned long lock_flags;

	/* Add this command block to pending cmd pool. We do this prior to
	 * writting IOARCB to ioarrin because IOA might complete the command
	 * by the time we are about to add it to the list. Response handler
	 * (isr/tasklet) looks for cmd block in the pending pending list.
	 */
	spin_lock_irqsave(&pinstance->pending_pool_lock, lock_flags);
	list_add_tail(&cmd->free_list, &pinstance->pending_cmd_pool);
	spin_unlock_irqrestore(&pinstance->pending_pool_lock, lock_flags);
	atomic_inc(&pinstance->outstanding_cmds);

	/* driver writes lower 32-bit value of IOARCB address only */
	mb();
	iowrite32(le32_to_cpu(cmd->ioa_cb->ioarcb.ioarcb_bus_addr),
		  pinstance->ioarrin);
}