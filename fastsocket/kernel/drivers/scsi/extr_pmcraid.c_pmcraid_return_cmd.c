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
struct pmcraid_instance {int /*<<< orphan*/  free_pool_lock; int /*<<< orphan*/  free_cmd_pool; } ;
struct pmcraid_cmd {int /*<<< orphan*/  free_list; struct pmcraid_instance* drv_inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pmcraid_return_cmd(struct pmcraid_cmd *cmd)
{
	struct pmcraid_instance *pinstance = cmd->drv_inst;
	unsigned long lock_flags;

	spin_lock_irqsave(&pinstance->free_pool_lock, lock_flags);
	list_add_tail(&cmd->free_list, &pinstance->free_cmd_pool);
	spin_unlock_irqrestore(&pinstance->free_pool_lock, lock_flags);
}