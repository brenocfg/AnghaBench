#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct ibmvfc_host {TYPE_2__* host; int /*<<< orphan*/  queue; int /*<<< orphan*/  work_thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; TYPE_1__ shost_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  IBMVFC_HOST_OFFLINE ; 
 int /*<<< orphan*/  LEAVE ; 
 struct ibmvfc_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_remove_host (TYPE_2__*) ; 
 int /*<<< orphan*/  ibmvfc_driver_lock ; 
 int /*<<< orphan*/  ibmvfc_free_event_pool (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_free_mem (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_link_down (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_purge_requests (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_release_crq_queue (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_remove_trace_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmvfc_trace_attr ; 
 int /*<<< orphan*/  ibmvfc_wait_while_resetting (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_2__*) ; 
 int /*<<< orphan*/  scsi_remove_host (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ibmvfc_remove(struct vio_dev *vdev)
{
	struct ibmvfc_host *vhost = dev_get_drvdata(&vdev->dev);
	unsigned long flags;

	ENTER;
	ibmvfc_remove_trace_file(&vhost->host->shost_dev.kobj, &ibmvfc_trace_attr);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_link_down(vhost, IBMVFC_HOST_OFFLINE);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	ibmvfc_wait_while_resetting(vhost);
	ibmvfc_release_crq_queue(vhost);
	kthread_stop(vhost->work_thread);
	fc_remove_host(vhost->host);
	scsi_remove_host(vhost->host);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_purge_requests(vhost, DID_ERROR);
	ibmvfc_free_event_pool(vhost);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	ibmvfc_free_mem(vhost);
	spin_lock(&ibmvfc_driver_lock);
	list_del(&vhost->queue);
	spin_unlock(&ibmvfc_driver_lock);
	scsi_host_put(vhost->host);
	LEAVE;
	return 0;
}