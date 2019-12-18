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
struct scsi_device {int queue_depth; TYPE_1__* host; } ;
struct ata_port {int /*<<< orphan*/  lock; } ;
struct ata_device {int /*<<< orphan*/  id; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ can_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DFLAG_NCQ_OFF ; 
 scalar_t__ ATA_MAX_QUEUE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MSG_SIMPLE_TAG ; 
 int SCSI_QDEPTH_DEFAULT ; 
 int /*<<< orphan*/  ata_dev_enabled (struct ata_device*) ; 
 scalar_t__ ata_id_queue_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_ncq_enabled (struct ata_device*) ; 
 struct ata_device* ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int __ata_change_queue_depth(struct ata_port *ap, struct scsi_device *sdev,
			     int queue_depth, int reason)
{
	struct ata_device *dev;
	unsigned long flags;

	if (reason != SCSI_QDEPTH_DEFAULT)
		return -EOPNOTSUPP;

	if (queue_depth < 1 || queue_depth == sdev->queue_depth)
		return sdev->queue_depth;

	dev = ata_scsi_find_dev(ap, sdev);
	if (!dev || !ata_dev_enabled(dev))
		return sdev->queue_depth;

	/* NCQ enabled? */
	spin_lock_irqsave(ap->lock, flags);
	dev->flags &= ~ATA_DFLAG_NCQ_OFF;
	if (queue_depth == 1 || !ata_ncq_enabled(dev)) {
		dev->flags |= ATA_DFLAG_NCQ_OFF;
		queue_depth = 1;
	}
	spin_unlock_irqrestore(ap->lock, flags);

	/* limit and apply queue depth */
	queue_depth = min(queue_depth, sdev->host->can_queue);
	queue_depth = min(queue_depth, ata_id_queue_depth(dev->id));
	queue_depth = min(queue_depth, ATA_MAX_QUEUE - 1);

	if (sdev->queue_depth == queue_depth)
		return -EINVAL;

	scsi_adjust_queue_depth(sdev, MSG_SIMPLE_TAG, queue_depth);
	return queue_depth;
}