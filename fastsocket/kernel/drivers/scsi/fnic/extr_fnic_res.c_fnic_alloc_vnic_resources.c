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
struct wq_enet_desc {int dummy; } ;
struct rq_enet_desc {int dummy; } ;
struct TYPE_3__ {unsigned int wq_enet_desc_count; int wq_copy_desc_count; unsigned int rq_desc_count; int /*<<< orphan*/  intr_timer_type; int /*<<< orphan*/  intr_timer; } ;
struct fnic {unsigned int wq_copy_count; unsigned int raw_wq_count; unsigned int rq_count; unsigned int cq_count; unsigned int intr_count; unsigned int err_intr_offset; int /*<<< orphan*/  vdev; TYPE_2__* lport; int /*<<< orphan*/  stats; TYPE_1__ config; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * wq_copy; int /*<<< orphan*/ * wq; int /*<<< orphan*/ * rq; int /*<<< orphan*/  legacy_pba; int /*<<< orphan*/  wq_count; } ;
struct fcpio_host_req {int dummy; } ;
struct fcpio_fw_req {int dummy; } ;
struct cq_enet_wq_desc {int dummy; } ;
struct cq_enet_rq_desc {int dummy; } ;
typedef  enum vnic_dev_intr_mode { ____Placeholder_vnic_dev_intr_mode } vnic_dev_intr_mode ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  RES_TYPE_INTR_PBA_LEGACY ; 
#define  VNIC_DEV_INTR_MODE_INTX 130 
#define  VNIC_DEV_INTR_MODE_MSI 129 
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int /*<<< orphan*/  fnic_free_vnic_resources (struct fnic*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int vnic_cq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  vnic_cq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_get_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_stats_clear (int /*<<< orphan*/ ) ; 
 int vnic_dev_stats_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vnic_intr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  vnic_intr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int vnic_rq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  vnic_rq_init (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int) ; 
 int vnic_wq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 
 int vnic_wq_copy_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int,int) ; 
 int /*<<< orphan*/  vnic_wq_copy_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vnic_wq_init (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int) ; 

int fnic_alloc_vnic_resources(struct fnic *fnic)
{
	enum vnic_dev_intr_mode intr_mode;
	unsigned int mask_on_assertion;
	unsigned int interrupt_offset;
	unsigned int error_interrupt_enable;
	unsigned int error_interrupt_offset;
	unsigned int i, cq_index;
	unsigned int wq_copy_cq_desc_count;
	int err;

	intr_mode = vnic_dev_get_intr_mode(fnic->vdev);

	shost_printk(KERN_INFO, fnic->lport->host, "vNIC interrupt mode: %s\n",
		     intr_mode == VNIC_DEV_INTR_MODE_INTX ? "legacy PCI INTx" :
		     intr_mode == VNIC_DEV_INTR_MODE_MSI ? "MSI" :
		     intr_mode == VNIC_DEV_INTR_MODE_MSIX ?
		     "MSI-X" : "unknown");

	shost_printk(KERN_INFO, fnic->lport->host, "vNIC resources avail: "
		     "wq %d cp_wq %d raw_wq %d rq %d cq %d intr %d\n",
		     fnic->wq_count, fnic->wq_copy_count, fnic->raw_wq_count,
		     fnic->rq_count, fnic->cq_count, fnic->intr_count);

	/* Allocate Raw WQ used for FCS frames */
	for (i = 0; i < fnic->raw_wq_count; i++) {
		err = vnic_wq_alloc(fnic->vdev, &fnic->wq[i], i,
			fnic->config.wq_enet_desc_count,
			sizeof(struct wq_enet_desc));
		if (err)
			goto err_out_cleanup;
	}

	/* Allocate Copy WQs used for SCSI IOs */
	for (i = 0; i < fnic->wq_copy_count; i++) {
		err = vnic_wq_copy_alloc(fnic->vdev, &fnic->wq_copy[i],
			(fnic->raw_wq_count + i),
			fnic->config.wq_copy_desc_count,
			sizeof(struct fcpio_host_req));
		if (err)
			goto err_out_cleanup;
	}

	/* RQ for receiving FCS frames */
	for (i = 0; i < fnic->rq_count; i++) {
		err = vnic_rq_alloc(fnic->vdev, &fnic->rq[i], i,
			fnic->config.rq_desc_count,
			sizeof(struct rq_enet_desc));
		if (err)
			goto err_out_cleanup;
	}

	/* CQ for each RQ */
	for (i = 0; i < fnic->rq_count; i++) {
		cq_index = i;
		err = vnic_cq_alloc(fnic->vdev,
			&fnic->cq[cq_index], cq_index,
			fnic->config.rq_desc_count,
			sizeof(struct cq_enet_rq_desc));
		if (err)
			goto err_out_cleanup;
	}

	/* CQ for each WQ */
	for (i = 0; i < fnic->raw_wq_count; i++) {
		cq_index = fnic->rq_count + i;
		err = vnic_cq_alloc(fnic->vdev, &fnic->cq[cq_index], cq_index,
			fnic->config.wq_enet_desc_count,
			sizeof(struct cq_enet_wq_desc));
		if (err)
			goto err_out_cleanup;
	}

	/* CQ for each COPY WQ */
	wq_copy_cq_desc_count = (fnic->config.wq_copy_desc_count * 3);
	for (i = 0; i < fnic->wq_copy_count; i++) {
		cq_index = fnic->raw_wq_count + fnic->rq_count + i;
		err = vnic_cq_alloc(fnic->vdev, &fnic->cq[cq_index],
			cq_index,
			wq_copy_cq_desc_count,
			sizeof(struct fcpio_fw_req));
		if (err)
			goto err_out_cleanup;
	}

	for (i = 0; i < fnic->intr_count; i++) {
		err = vnic_intr_alloc(fnic->vdev, &fnic->intr[i], i);
		if (err)
			goto err_out_cleanup;
	}

	fnic->legacy_pba = vnic_dev_get_res(fnic->vdev,
				RES_TYPE_INTR_PBA_LEGACY, 0);

	if (!fnic->legacy_pba && intr_mode == VNIC_DEV_INTR_MODE_INTX) {
		shost_printk(KERN_ERR, fnic->lport->host,
			     "Failed to hook legacy pba resource\n");
		err = -ENODEV;
		goto err_out_cleanup;
	}

	/*
	 * Init RQ/WQ resources.
	 *
	 * RQ[0 to n-1] point to CQ[0 to n-1]
	 * WQ[0 to m-1] point to CQ[n to n+m-1]
	 * WQ_COPY[0 to k-1] points to CQ[n+m to n+m+k-1]
	 *
	 * Note for copy wq we always initialize with cq_index = 0
	 *
	 * Error interrupt is not enabled for MSI.
	 */

	switch (intr_mode) {
	case VNIC_DEV_INTR_MODE_INTX:
	case VNIC_DEV_INTR_MODE_MSIX:
		error_interrupt_enable = 1;
		error_interrupt_offset = fnic->err_intr_offset;
		break;
	default:
		error_interrupt_enable = 0;
		error_interrupt_offset = 0;
		break;
	}

	for (i = 0; i < fnic->rq_count; i++) {
		cq_index = i;
		vnic_rq_init(&fnic->rq[i],
			     cq_index,
			     error_interrupt_enable,
			     error_interrupt_offset);
	}

	for (i = 0; i < fnic->raw_wq_count; i++) {
		cq_index = i + fnic->rq_count;
		vnic_wq_init(&fnic->wq[i],
			     cq_index,
			     error_interrupt_enable,
			     error_interrupt_offset);
	}

	for (i = 0; i < fnic->wq_copy_count; i++) {
		vnic_wq_copy_init(&fnic->wq_copy[i],
				  0 /* cq_index 0 - always */,
				  error_interrupt_enable,
				  error_interrupt_offset);
	}

	for (i = 0; i < fnic->cq_count; i++) {

		switch (intr_mode) {
		case VNIC_DEV_INTR_MODE_MSIX:
			interrupt_offset = i;
			break;
		default:
			interrupt_offset = 0;
			break;
		}

		vnic_cq_init(&fnic->cq[i],
			0 /* flow_control_enable */,
			1 /* color_enable */,
			0 /* cq_head */,
			0 /* cq_tail */,
			1 /* cq_tail_color */,
			1 /* interrupt_enable */,
			1 /* cq_entry_enable */,
			0 /* cq_message_enable */,
			interrupt_offset,
			0 /* cq_message_addr */);
	}

	/*
	 * Init INTR resources
	 *
	 * mask_on_assertion is not used for INTx due to the level-
	 * triggered nature of INTx
	 */

	switch (intr_mode) {
	case VNIC_DEV_INTR_MODE_MSI:
	case VNIC_DEV_INTR_MODE_MSIX:
		mask_on_assertion = 1;
		break;
	default:
		mask_on_assertion = 0;
		break;
	}

	for (i = 0; i < fnic->intr_count; i++) {
		vnic_intr_init(&fnic->intr[i],
			fnic->config.intr_timer,
			fnic->config.intr_timer_type,
			mask_on_assertion);
	}

	/* init the stats memory by making the first call here */
	err = vnic_dev_stats_dump(fnic->vdev, &fnic->stats);
	if (err) {
		shost_printk(KERN_ERR, fnic->lport->host,
			     "vnic_dev_stats_dump failed - x%x\n", err);
		goto err_out_cleanup;
	}

	/* Clear LIF stats */
	vnic_dev_stats_clear(fnic->vdev);

	return 0;

err_out_cleanup:
	fnic_free_vnic_resources(fnic);

	return err;
}