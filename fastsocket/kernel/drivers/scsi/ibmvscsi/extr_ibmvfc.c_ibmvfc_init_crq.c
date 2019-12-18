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
struct vio_dev {int /*<<< orphan*/  unit_address; int /*<<< orphan*/  irq; } ;
struct ibmvfc_crq_queue {int size; struct ibmvfc_crq* msgs; int /*<<< orphan*/  msg_token; scalar_t__ cur; } ;
struct ibmvfc_host {int /*<<< orphan*/  tasklet; struct ibmvfc_crq_queue crq; struct device* dev; } ;
struct ibmvfc_crq {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int H_BUSY ; 
 int H_CLOSED ; 
 int /*<<< orphan*/  H_FREE_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (int) ; 
 int /*<<< orphan*/  H_REG_CRQ ; 
 int H_RESOURCE ; 
 int /*<<< orphan*/  IBMVFC_NAME ; 
 int /*<<< orphan*/  LEAVE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,struct ibmvfc_crq*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_interrupt ; 
 int ibmvfc_reset_crq (struct ibmvfc_host*) ; 
 scalar_t__ ibmvfc_tasklet ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibmvfc_host*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void*,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 
 int vio_enable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static int ibmvfc_init_crq(struct ibmvfc_host *vhost)
{
	int rc, retrc = -ENOMEM;
	struct device *dev = vhost->dev;
	struct vio_dev *vdev = to_vio_dev(dev);
	struct ibmvfc_crq_queue *crq = &vhost->crq;

	ENTER;
	crq->msgs = (struct ibmvfc_crq *)get_zeroed_page(GFP_KERNEL);

	if (!crq->msgs)
		return -ENOMEM;

	crq->size = PAGE_SIZE / sizeof(*crq->msgs);
	crq->msg_token = dma_map_single(dev, crq->msgs,
					PAGE_SIZE, DMA_BIDIRECTIONAL);

	if (dma_mapping_error(dev, crq->msg_token))
		goto map_failed;

	retrc = rc = plpar_hcall_norets(H_REG_CRQ, vdev->unit_address,
					crq->msg_token, PAGE_SIZE);

	if (rc == H_RESOURCE)
		/* maybe kexecing and resource is busy. try a reset */
		retrc = rc = ibmvfc_reset_crq(vhost);

	if (rc == H_CLOSED)
		dev_warn(dev, "Partner adapter not ready\n");
	else if (rc) {
		dev_warn(dev, "Error %d opening adapter\n", rc);
		goto reg_crq_failed;
	}

	retrc = 0;

	tasklet_init(&vhost->tasklet, (void *)ibmvfc_tasklet, (unsigned long)vhost);

	if ((rc = request_irq(vdev->irq, ibmvfc_interrupt, 0, IBMVFC_NAME, vhost))) {
		dev_err(dev, "Couldn't register irq 0x%x. rc=%d\n", vdev->irq, rc);
		goto req_irq_failed;
	}

	if ((rc = vio_enable_interrupts(vdev))) {
		dev_err(dev, "Error %d enabling interrupts\n", rc);
		goto req_irq_failed;
	}

	crq->cur = 0;
	LEAVE;
	return retrc;

req_irq_failed:
	tasklet_kill(&vhost->tasklet);
	do {
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	} while (rc == H_BUSY || H_IS_LONG_BUSY(rc));
reg_crq_failed:
	dma_unmap_single(dev, crq->msg_token, PAGE_SIZE, DMA_BIDIRECTIONAL);
map_failed:
	free_page((unsigned long)crq->msgs);
	return retrc;
}