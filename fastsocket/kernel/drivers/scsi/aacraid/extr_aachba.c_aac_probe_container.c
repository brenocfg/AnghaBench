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
struct TYPE_4__ {int Status; } ;
struct TYPE_3__ {int /*<<< orphan*/ * next; } ;
struct scsi_device {void (* scsi_done ) (struct scsi_device*) ;int id; TYPE_2__ SCp; struct scsi_device* device; int /*<<< orphan*/  host; scalar_t__ sdev_state; TYPE_1__ list; } ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_device*) ;int id; TYPE_2__ SCp; struct scsi_cmnd* device; int /*<<< orphan*/  host; scalar_t__ sdev_state; TYPE_1__ list; } ;
struct aac_dev {int /*<<< orphan*/  scsi_host_ptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ _aac_probe_container (struct scsi_device*,scalar_t__) ; 
 scalar_t__ aac_probe_container_callback1 ; 
 int /*<<< orphan*/  kfree (struct scsi_device*) ; 
 struct scsi_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 

int aac_probe_container(struct aac_dev *dev, int cid)
{
	struct scsi_cmnd *scsicmd = kmalloc(sizeof(*scsicmd), GFP_KERNEL);
	struct scsi_device *scsidev = kmalloc(sizeof(*scsidev), GFP_KERNEL);
	int status;

	if (!scsicmd || !scsidev) {
		kfree(scsicmd);
		kfree(scsidev);
		return -ENOMEM;
	}
	scsicmd->list.next = NULL;
	scsicmd->scsi_done = (void (*)(struct scsi_cmnd*))aac_probe_container_callback1;

	scsicmd->device = scsidev;
	scsidev->sdev_state = 0;
	scsidev->id = cid;
	scsidev->host = dev->scsi_host_ptr;

	if (_aac_probe_container(scsicmd, aac_probe_container_callback1) == 0)
		while (scsicmd->device == scsidev)
			schedule();
	kfree(scsidev);
	status = scsicmd->SCp.Status;
	kfree(scsicmd);
	return status;
}