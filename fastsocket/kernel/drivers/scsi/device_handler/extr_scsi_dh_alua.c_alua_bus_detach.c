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
struct scsi_dh_data {scalar_t__ buf; } ;
struct scsi_device {TYPE_1__* request_queue; struct scsi_dh_data* scsi_dh_data; } ;
struct alua_dh_data {scalar_t__ buff; scalar_t__ inq; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_DH_NAME ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree (struct scsi_dh_data*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void alua_bus_detach(struct scsi_device *sdev)
{
	struct scsi_dh_data *scsi_dh_data;
	struct alua_dh_data *h;
	unsigned long flags;

	spin_lock_irqsave(sdev->request_queue->queue_lock, flags);
	scsi_dh_data = sdev->scsi_dh_data;
	sdev->scsi_dh_data = NULL;
	spin_unlock_irqrestore(sdev->request_queue->queue_lock, flags);

	h = (struct alua_dh_data *) scsi_dh_data->buf;
	if (h->buff && h->inq != h->buff)
		kfree(h->buff);
	kfree(scsi_dh_data);
	module_put(THIS_MODULE);
	sdev_printk(KERN_NOTICE, sdev, "%s: Detached\n", ALUA_DH_NAME);
}