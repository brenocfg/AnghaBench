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
struct TYPE_4__ {int protocol; int flags; } ;
struct ata_queued_cmd {TYPE_2__ tf; struct ata_port* ap; } ;
struct ata_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  hsm_task_state; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sff_tf_load ) (struct ata_port*,TYPE_2__*) ;} ;

/* Variables and functions */
#define  ATAPI_PROT_DMA 129 
#define  ATA_PROT_DMA 128 
 int ATA_TFLAG_POLLING ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  HSM_ST_LAST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  octeon_cf_dma_setup (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  octeon_cf_dma_start (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,TYPE_2__*) ; 

__attribute__((used)) static unsigned int octeon_cf_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;

	switch (qc->tf.protocol) {
	case ATA_PROT_DMA:
		WARN_ON(qc->tf.flags & ATA_TFLAG_POLLING);

		ap->ops->sff_tf_load(ap, &qc->tf);  /* load tf registers */
		octeon_cf_dma_setup(qc);	    /* set up dma */
		octeon_cf_dma_start(qc);	    /* initiate dma */
		ap->hsm_task_state = HSM_ST_LAST;
		break;

	case ATAPI_PROT_DMA:
		dev_err(ap->dev, "Error, ATAPI not supported\n");
		BUG();

	default:
		return ata_sff_qc_issue(qc);
	}

	return 0;
}