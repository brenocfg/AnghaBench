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
struct viosrp_crq {int dummy; } ;
struct vio_dev {int irq; int /*<<< orphan*/  unit_address; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  srp_task; } ;
struct crq_queue {int size; struct viosrp_crq* msgs; int /*<<< orphan*/  msg_token; int /*<<< orphan*/  lock; scalar_t__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int H_BUSY ; 
 int /*<<< orphan*/  H_FREE_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (int) ; 
 int /*<<< orphan*/  H_REG_CRQ ; 
 int H_RESOURCE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,struct viosrp_crq*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  gather_partition_info () ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  rpavscsi_handle_event ; 
 int rpavscsi_reset_crq_queue (struct crq_queue*,struct ibmvscsi_host_data*) ; 
 scalar_t__ rpavscsi_task ; 
 int /*<<< orphan*/  set_adapter_info (struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void*,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 
 int vio_enable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static int rpavscsi_init_crq_queue(struct crq_queue *queue,
				   struct ibmvscsi_host_data *hostdata,
				   int max_requests)
{
	int rc;
	int retrc;
	struct vio_dev *vdev = to_vio_dev(hostdata->dev);

	queue->msgs = (struct viosrp_crq *)get_zeroed_page(GFP_KERNEL);

	if (!queue->msgs)
		goto malloc_failed;
	queue->size = PAGE_SIZE / sizeof(*queue->msgs);

	queue->msg_token = dma_map_single(hostdata->dev, queue->msgs,
					  queue->size * sizeof(*queue->msgs),
					  DMA_BIDIRECTIONAL);

	if (dma_mapping_error(hostdata->dev, queue->msg_token))
		goto map_failed;

	gather_partition_info();
	set_adapter_info(hostdata);

	retrc = rc = plpar_hcall_norets(H_REG_CRQ,
				vdev->unit_address,
				queue->msg_token, PAGE_SIZE);
	if (rc == H_RESOURCE)
		/* maybe kexecing and resource is busy. try a reset */
		rc = rpavscsi_reset_crq_queue(queue,
					      hostdata);

	if (rc == 2) {
		/* Adapter is good, but other end is not ready */
		dev_warn(hostdata->dev, "Partner adapter not ready\n");
		retrc = 0;
	} else if (rc != 0) {
		dev_warn(hostdata->dev, "Error %d opening adapter\n", rc);
		goto reg_crq_failed;
	}

	queue->cur = 0;
	spin_lock_init(&queue->lock);

	tasklet_init(&hostdata->srp_task, (void *)rpavscsi_task,
		     (unsigned long)hostdata);

	if (request_irq(vdev->irq,
			rpavscsi_handle_event,
			0, "ibmvscsi", (void *)hostdata) != 0) {
		dev_err(hostdata->dev, "couldn't register irq 0x%x\n",
			vdev->irq);
		goto req_irq_failed;
	}

	rc = vio_enable_interrupts(vdev);
	if (rc != 0) {
		dev_err(hostdata->dev, "Error %d enabling interrupts!!!\n", rc);
		goto req_irq_failed;
	}

	return retrc;

      req_irq_failed:
	tasklet_kill(&hostdata->srp_task);
	rc = 0;
	do {
		if (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	} while ((rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));
      reg_crq_failed:
	dma_unmap_single(hostdata->dev,
			 queue->msg_token,
			 queue->size * sizeof(*queue->msgs), DMA_BIDIRECTIONAL);
      map_failed:
	free_page((unsigned long)queue->msgs);
      malloc_failed:
	return -1;
}