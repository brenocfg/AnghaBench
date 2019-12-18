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
struct scsi_dh_data {scalar_t__ buf; int /*<<< orphan*/ * scsi_dh; } ;
struct scsi_device {TYPE_1__* request_queue; struct scsi_dh_data* scsi_dh_data; } ;
struct hp_sw_dh_data {scalar_t__ path_state; struct scsi_device* sdev; int /*<<< orphan*/  retries; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HP_SW_NAME ; 
 scalar_t__ HP_SW_PATH_ACTIVE ; 
 scalar_t__ HP_SW_PATH_UNINITIALIZED ; 
 int /*<<< orphan*/  HP_SW_RETRIES ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_DH_OK ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  hp_sw_dh ; 
 int hp_sw_tur (struct scsi_device*,struct hp_sw_dh_data*) ; 
 int /*<<< orphan*/  kfree (struct scsi_dh_data*) ; 
 struct scsi_dh_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hp_sw_bus_attach(struct scsi_device *sdev)
{
	struct scsi_dh_data *scsi_dh_data;
	struct hp_sw_dh_data *h;
	unsigned long flags;
	int ret;

	scsi_dh_data = kzalloc(sizeof(*scsi_dh_data)
			       + sizeof(*h) , GFP_KERNEL);
	if (!scsi_dh_data) {
		sdev_printk(KERN_ERR, sdev, "%s: Attach Failed\n",
			    HP_SW_NAME);
		return 0;
	}

	scsi_dh_data->scsi_dh = &hp_sw_dh;
	h = (struct hp_sw_dh_data *) scsi_dh_data->buf;
	h->path_state = HP_SW_PATH_UNINITIALIZED;
	h->retries = HP_SW_RETRIES;
	h->sdev = sdev;

	ret = hp_sw_tur(sdev, h);
	if (ret != SCSI_DH_OK || h->path_state == HP_SW_PATH_UNINITIALIZED)
		goto failed;

	if (!try_module_get(THIS_MODULE))
		goto failed;

	spin_lock_irqsave(sdev->request_queue->queue_lock, flags);
	sdev->scsi_dh_data = scsi_dh_data;
	spin_unlock_irqrestore(sdev->request_queue->queue_lock, flags);

	sdev_printk(KERN_INFO, sdev, "%s: attached to %s path\n",
		    HP_SW_NAME, h->path_state == HP_SW_PATH_ACTIVE?
		    "active":"passive");

	return 0;

failed:
	kfree(scsi_dh_data);
	sdev_printk(KERN_ERR, sdev, "%s: not attached\n",
		    HP_SW_NAME);
	return -EINVAL;
}