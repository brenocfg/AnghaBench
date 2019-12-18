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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ata_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  park_req_pending; } ;
struct ata_device {scalar_t__ class; int flags; size_t devno; TYPE_2__* link; int /*<<< orphan*/  unpark_deadline; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dev_action; } ;
struct TYPE_4__ {TYPE_1__ eh_info; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 int ATA_DFLAG_NO_UNLOAD ; 
 int /*<<< orphan*/  ATA_EH_PARK ; 
 long ATA_TMOUT_MAX_PARK ; 
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  ata_deadline (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  ata_port_schedule_eh (struct ata_port*) ; 
 struct ata_device* ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int strict_strtol (char const*,int,long*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t ata_scsi_park_store(struct device *device,
				   struct device_attribute *attr,
				   const char *buf, size_t len)
{
	struct scsi_device *sdev = to_scsi_device(device);
	struct ata_port *ap;
	struct ata_device *dev;
	long int input;
	unsigned long flags;
	int rc;

	rc = strict_strtol(buf, 10, &input);
	if (rc || input < -2)
		return -EINVAL;
	if (input > ATA_TMOUT_MAX_PARK) {
		rc = -EOVERFLOW;
		input = ATA_TMOUT_MAX_PARK;
	}

	ap = ata_shost_to_port(sdev->host);

	spin_lock_irqsave(ap->lock, flags);
	dev = ata_scsi_find_dev(ap, sdev);
	if (unlikely(!dev)) {
		rc = -ENODEV;
		goto unlock;
	}
	if (dev->class != ATA_DEV_ATA) {
		rc = -EOPNOTSUPP;
		goto unlock;
	}

	if (input >= 0) {
		if (dev->flags & ATA_DFLAG_NO_UNLOAD) {
			rc = -EOPNOTSUPP;
			goto unlock;
		}

		dev->unpark_deadline = ata_deadline(jiffies, input);
		dev->link->eh_info.dev_action[dev->devno] |= ATA_EH_PARK;
		ata_port_schedule_eh(ap);
		complete(&ap->park_req_pending);
	} else {
		switch (input) {
		case -1:
			dev->flags &= ~ATA_DFLAG_NO_UNLOAD;
			break;
		case -2:
			dev->flags |= ATA_DFLAG_NO_UNLOAD;
			break;
		}
	}
unlock:
	spin_unlock_irqrestore(ap->lock, flags);

	return rc ? rc : len;
}