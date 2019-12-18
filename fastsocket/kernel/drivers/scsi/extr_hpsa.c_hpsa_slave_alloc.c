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
struct scsi_device {struct hpsa_scsi_dev_t* hostdata; int /*<<< orphan*/  lun; } ;
struct hpsa_scsi_dev_t {int dummy; } ;
struct ctlr_info {int /*<<< orphan*/  devlock; } ;

/* Variables and functions */
 struct hpsa_scsi_dev_t* lookup_hpsa_scsi_dev (struct ctlr_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_channel (struct scsi_device*) ; 
 int /*<<< orphan*/  sdev_id (struct scsi_device*) ; 
 struct ctlr_info* sdev_to_hba (struct scsi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hpsa_slave_alloc(struct scsi_device *sdev)
{
	struct hpsa_scsi_dev_t *sd;
	unsigned long flags;
	struct ctlr_info *h;

	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->devlock, flags);
	sd = lookup_hpsa_scsi_dev(h, sdev_channel(sdev),
		sdev_id(sdev), sdev->lun);
	if (sd != NULL)
		sdev->hostdata = sd;
	spin_unlock_irqrestore(&h->devlock, flags);
	return 0;
}