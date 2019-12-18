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
struct scsi_dh_data {scalar_t__ buf; } ;
struct scsi_device {TYPE_1__* request_queue; struct scsi_dh_data* scsi_dh_data; } ;
struct rdac_dh_data {TYPE_2__* ctlr; } ;
struct TYPE_4__ {int /*<<< orphan*/  kref; scalar_t__ ms_queued; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  RDAC_NAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scsi_dh_data*) ; 
 int /*<<< orphan*/  kmpath_rdacd ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_controller ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void rdac_bus_detach( struct scsi_device *sdev )
{
	struct scsi_dh_data *scsi_dh_data;
	struct rdac_dh_data *h;
	unsigned long flags;

	scsi_dh_data = sdev->scsi_dh_data;
	h = (struct rdac_dh_data *) scsi_dh_data->buf;
	if (h->ctlr && h->ctlr->ms_queued)
		flush_workqueue(kmpath_rdacd);

	spin_lock_irqsave(sdev->request_queue->queue_lock, flags);
	sdev->scsi_dh_data = NULL;
	spin_unlock_irqrestore(sdev->request_queue->queue_lock, flags);

	spin_lock(&list_lock);
	if (h->ctlr)
		kref_put(&h->ctlr->kref, release_controller);
	spin_unlock(&list_lock);
	kfree(scsi_dh_data);
	module_put(THIS_MODULE);
	sdev_printk(KERN_NOTICE, sdev, "%s: Detached\n", RDAC_NAME);
}