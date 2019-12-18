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
struct scsi_cmnd {int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  cmd_pool; int /*<<< orphan*/  free_list_lock; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  scsi_pool_free_command (int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __scsi_put_command(struct Scsi_Host *shost, struct scsi_cmnd *cmd,
			struct device *dev)
{
	unsigned long flags;

	/* changing locks here, don't need to restore the irq state */
	spin_lock_irqsave(&shost->free_list_lock, flags);
	if (unlikely(list_empty(&shost->free_list))) {
		list_add(&cmd->list, &shost->free_list);
		cmd = NULL;
	}
	spin_unlock_irqrestore(&shost->free_list_lock, flags);

	if (likely(cmd != NULL))
		scsi_pool_free_command(shost->cmd_pool, cmd);

	put_device(dev);
}