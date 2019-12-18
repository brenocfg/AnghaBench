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
struct viosrp_crq {int valid; } ;
struct vio_dev {int dummy; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  queue; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct viosrp_crq* crq_queue_next_crq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmvscsi_handle_crq (struct viosrp_crq*,struct ibmvscsi_host_data*) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_disable_interrupts (struct vio_dev*) ; 
 int /*<<< orphan*/  vio_enable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static void rpavscsi_task(void *data)
{
	struct ibmvscsi_host_data *hostdata = (struct ibmvscsi_host_data *)data;
	struct vio_dev *vdev = to_vio_dev(hostdata->dev);
	struct viosrp_crq *crq;
	int done = 0;

	while (!done) {
		/* Pull all the valid messages off the CRQ */
		while ((crq = crq_queue_next_crq(&hostdata->queue)) != NULL) {
			ibmvscsi_handle_crq(crq, hostdata);
			crq->valid = 0x00;
		}

		vio_enable_interrupts(vdev);
		if ((crq = crq_queue_next_crq(&hostdata->queue)) != NULL) {
			vio_disable_interrupts(vdev);
			ibmvscsi_handle_crq(crq, hostdata);
			crq->valid = 0x00;
		} else {
			done = 1;
		}
	}
}