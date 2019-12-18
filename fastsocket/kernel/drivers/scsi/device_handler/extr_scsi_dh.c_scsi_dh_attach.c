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
struct scsi_device_handler {int dummy; } ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; struct scsi_device* queuedata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 struct scsi_device_handler* get_device_handler (char const*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int scsi_dh_handler_attach (struct scsi_device*,struct scsi_device_handler*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int scsi_dh_attach(struct request_queue *q, const char *name)
{
	unsigned long flags;
	struct scsi_device *sdev;
	struct scsi_device_handler *scsi_dh;
	int err = 0;

	scsi_dh = get_device_handler(name);
	if (!scsi_dh)
		return -EINVAL;

	spin_lock_irqsave(q->queue_lock, flags);
	sdev = q->queuedata;
	if (!sdev || !get_device(&sdev->sdev_gendev))
		err = -ENODEV;
	spin_unlock_irqrestore(q->queue_lock, flags);

	if (!err) {
		err = scsi_dh_handler_attach(sdev, scsi_dh);
		put_device(&sdev->sdev_gendev);
	}
	return err;
}