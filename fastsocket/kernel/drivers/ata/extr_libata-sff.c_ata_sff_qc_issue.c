#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int protocol; int flags; } ;
struct ata_queued_cmd {TYPE_2__* dev; TYPE_3__ tf; struct ata_port* ap; } ;
struct ata_port {int flags; void* hsm_task_state; TYPE_1__* ops; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  devno; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* bmdma_setup ) (struct ata_queued_cmd*) ;int /*<<< orphan*/  (* sff_tf_load ) (struct ata_port*,TYPE_3__*) ;int /*<<< orphan*/  (* bmdma_start ) (struct ata_queued_cmd*) ;} ;

/* Variables and functions */
 unsigned int AC_ERR_SYSTEM ; 
#define  ATAPI_PROT_DMA 133 
#define  ATAPI_PROT_NODATA 132 
#define  ATAPI_PROT_PIO 131 
 int ATA_DFLAG_CDB_INTR ; 
 int ATA_FLAG_PIO_POLLING ; 
#define  ATA_PROT_DMA 130 
#define  ATA_PROT_NODATA 129 
#define  ATA_PROT_PIO 128 
 int ATA_TFLAG_POLLING ; 
 int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  BUG () ; 
 void* HSM_ST ; 
 void* HSM_ST_FIRST ; 
 void* HSM_ST_LAST ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ata_dev_select (struct ata_port*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_qc_set_polling (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_sff_queue_pio_task (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_to_host (struct ata_port*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  stub3 (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  stub4 (struct ata_port*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub5 (struct ata_queued_cmd*) ; 

unsigned int ata_sff_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;

	/* Use polling pio if the LLD doesn't handle
	 * interrupt driven pio and atapi CDB interrupt.
	 */
	if (ap->flags & ATA_FLAG_PIO_POLLING) {
		switch (qc->tf.protocol) {
		case ATA_PROT_PIO:
		case ATA_PROT_NODATA:
		case ATAPI_PROT_PIO:
		case ATAPI_PROT_NODATA:
			qc->tf.flags |= ATA_TFLAG_POLLING;
			break;
		case ATAPI_PROT_DMA:
			if (qc->dev->flags & ATA_DFLAG_CDB_INTR)
				/* see ata_dma_blacklisted() */
				BUG();
			break;
		default:
			break;
		}
	}

	/* select the device */
	ata_dev_select(ap, qc->dev->devno, 1, 0);

	/* start the command */
	switch (qc->tf.protocol) {
	case ATA_PROT_NODATA:
		if (qc->tf.flags & ATA_TFLAG_POLLING)
			ata_qc_set_polling(qc);

		ata_tf_to_host(ap, &qc->tf);
		ap->hsm_task_state = HSM_ST_LAST;

		if (qc->tf.flags & ATA_TFLAG_POLLING)
			ata_sff_queue_pio_task(ap, 0);

		break;

	case ATA_PROT_DMA:
		WARN_ON_ONCE(qc->tf.flags & ATA_TFLAG_POLLING);

		ap->ops->sff_tf_load(ap, &qc->tf);  /* load tf registers */
		ap->ops->bmdma_setup(qc);	    /* set up bmdma */
		ap->ops->bmdma_start(qc);	    /* initiate bmdma */
		ap->hsm_task_state = HSM_ST_LAST;
		break;

	case ATA_PROT_PIO:
		if (qc->tf.flags & ATA_TFLAG_POLLING)
			ata_qc_set_polling(qc);

		ata_tf_to_host(ap, &qc->tf);

		if (qc->tf.flags & ATA_TFLAG_WRITE) {
			/* PIO data out protocol */
			ap->hsm_task_state = HSM_ST_FIRST;
			ata_sff_queue_pio_task(ap, 0);

			/* always send first data block using the
			 * ata_sff_pio_task() codepath.
			 */
		} else {
			/* PIO data in protocol */
			ap->hsm_task_state = HSM_ST;

			if (qc->tf.flags & ATA_TFLAG_POLLING)
				ata_sff_queue_pio_task(ap, 0);

			/* if polling, ata_sff_pio_task() handles the
			 * rest.  otherwise, interrupt handler takes
			 * over from here.
			 */
		}

		break;

	case ATAPI_PROT_PIO:
	case ATAPI_PROT_NODATA:
		if (qc->tf.flags & ATA_TFLAG_POLLING)
			ata_qc_set_polling(qc);

		ata_tf_to_host(ap, &qc->tf);

		ap->hsm_task_state = HSM_ST_FIRST;

		/* send cdb by polling if no cdb interrupt */
		if ((!(qc->dev->flags & ATA_DFLAG_CDB_INTR)) ||
		    (qc->tf.flags & ATA_TFLAG_POLLING))
			ata_sff_queue_pio_task(ap, 0);
		break;

	case ATAPI_PROT_DMA:
		WARN_ON_ONCE(qc->tf.flags & ATA_TFLAG_POLLING);

		ap->ops->sff_tf_load(ap, &qc->tf);  /* load tf registers */
		ap->ops->bmdma_setup(qc);	    /* set up bmdma */
		ap->hsm_task_state = HSM_ST_FIRST;

		/* send cdb by polling if no cdb interrupt */
		if (!(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			ata_sff_queue_pio_task(ap, 0);
		break;

	default:
		WARN_ON_ONCE(1);
		return AC_ERR_SYSTEM;
	}

	return 0;
}