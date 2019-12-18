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
struct scsi_device {int /*<<< orphan*/  sdev_gendev; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  cmd_list; int /*<<< orphan*/  host; } ;
struct scsi_cmnd {int /*<<< orphan*/  jiffies_at_alloc; int /*<<< orphan*/  list; struct scsi_device* device; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct scsi_cmnd* __scsi_get_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct scsi_cmnd *scsi_get_command(struct scsi_device *dev, gfp_t gfp_mask)
{
	struct scsi_cmnd *cmd;

	/* Bail if we can't get a reference to the device */
	if (!get_device(&dev->sdev_gendev))
		return NULL;

	cmd = __scsi_get_command(dev->host, gfp_mask);

	if (likely(cmd != NULL)) {
		unsigned long flags;

		cmd->device = dev;
		INIT_LIST_HEAD(&cmd->list);
		spin_lock_irqsave(&dev->list_lock, flags);
		list_add_tail(&cmd->list, &dev->cmd_list);
		spin_unlock_irqrestore(&dev->list_lock, flags);
		cmd->jiffies_at_alloc = jiffies;
	} else
		put_device(&dev->sdev_gendev);

	return cmd;
}