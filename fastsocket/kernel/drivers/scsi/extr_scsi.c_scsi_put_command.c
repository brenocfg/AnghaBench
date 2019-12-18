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
struct scsi_device {int /*<<< orphan*/  sdev_gendev; int /*<<< orphan*/  host; int /*<<< orphan*/  list_lock; } ;
struct scsi_cmnd {struct scsi_device* device; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __scsi_put_command (int /*<<< orphan*/ ,struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void scsi_put_command(struct scsi_cmnd *cmd)
{
	struct scsi_device *sdev = cmd->device;
	unsigned long flags;

	/* serious error if the command hasn't come from a device list */
	spin_lock_irqsave(&cmd->device->list_lock, flags);
	BUG_ON(list_empty(&cmd->list));
	list_del_init(&cmd->list);
	spin_unlock_irqrestore(&cmd->device->list_lock, flags);

	__scsi_put_command(cmd->device->host, cmd, &sdev->sdev_gendev);
}