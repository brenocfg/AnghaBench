#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_3__* device; } ;
struct hpsa_scsi_dev_t {int /*<<< orphan*/  scsi3addr; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct ctlr_info {TYPE_2__* pdev; TYPE_1__* scsi_host; } ;
struct TYPE_6__ {struct hpsa_scsi_dev_t* hostdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int hpsa_send_reset (struct ctlr_info*,int /*<<< orphan*/ ) ; 
 struct ctlr_info* sdev_to_hba (TYPE_3__*) ; 
 scalar_t__ wait_for_device_to_become_ready (struct ctlr_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_eh_device_reset_handler(struct scsi_cmnd *scsicmd)
{
	int rc;
	struct ctlr_info *h;
	struct hpsa_scsi_dev_t *dev;

	/* find the controller to which the command to be aborted was sent */
	h = sdev_to_hba(scsicmd->device);
	if (h == NULL) /* paranoia */
		return FAILED;
	dev = scsicmd->device->hostdata;
	if (!dev) {
		dev_err(&h->pdev->dev, "hpsa_eh_device_reset_handler: "
			"device lookup failed.\n");
		return FAILED;
	}
	dev_warn(&h->pdev->dev, "resetting device %d:%d:%d:%d\n",
		h->scsi_host->host_no, dev->bus, dev->target, dev->lun);
	/* send a reset to the SCSI LUN which the command was sent to */
	rc = hpsa_send_reset(h, dev->scsi3addr);
	if (rc == 0 && wait_for_device_to_become_ready(h, dev->scsi3addr) == 0)
		return SUCCESS;

	dev_warn(&h->pdev->dev, "resetting device failed.\n");
	return FAILED;
}