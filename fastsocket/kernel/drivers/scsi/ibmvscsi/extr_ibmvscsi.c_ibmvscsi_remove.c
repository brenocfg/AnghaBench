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
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  host; int /*<<< orphan*/  work_thread; int /*<<< orphan*/  queue; int /*<<< orphan*/  pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_crq_queue ) (int /*<<< orphan*/ *,struct ibmvscsi_host_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct ibmvscsi_host_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 TYPE_1__* ibmvscsi_ops ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_events ; 
 int /*<<< orphan*/  release_event_pool (int /*<<< orphan*/ *,struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct ibmvscsi_host_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_persist_bufs (struct ibmvscsi_host_data*) ; 

__attribute__((used)) static int ibmvscsi_remove(struct vio_dev *vdev)
{
	struct ibmvscsi_host_data *hostdata = dev_get_drvdata(&vdev->dev);
	unmap_persist_bufs(hostdata);
	release_event_pool(&hostdata->pool, hostdata);
	ibmvscsi_ops->release_crq_queue(&hostdata->queue, hostdata,
					max_events);

	kthread_stop(hostdata->work_thread);
	srp_remove_host(hostdata->host);
	scsi_remove_host(hostdata->host);
	scsi_host_put(hostdata->host);

	return 0;
}