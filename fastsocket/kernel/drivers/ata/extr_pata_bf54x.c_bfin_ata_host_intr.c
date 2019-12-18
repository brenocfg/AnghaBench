#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {scalar_t__ protocol; } ;
struct ata_queued_cmd {int err_mask; TYPE_3__ tf; TYPE_2__* dev; } ;
struct TYPE_9__ {int idle_irq; } ;
struct ata_eh_info {int dummy; } ;
struct TYPE_6__ {struct ata_eh_info eh_info; } ;
struct ata_port {int hsm_task_state; TYPE_5__* ops; TYPE_4__ stats; int /*<<< orphan*/  print_id; TYPE_1__ link; } ;
struct TYPE_10__ {int (* bmdma_status ) (struct ata_port*) ;int (* sff_check_altstatus ) (struct ata_port*) ;int (* sff_check_status ) (struct ata_port*) ;int /*<<< orphan*/  (* irq_ack ) (struct ata_port*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sff_irq_clear ) (struct ata_port*) ;int /*<<< orphan*/  (* bmdma_stop ) (struct ata_queued_cmd*) ;} ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int AC_ERR_HOST_BUS ; 
 scalar_t__ ATAPI_PROT_DMA ; 
 int ATA_BUSY ; 
 int ATA_DFLAG_CDB_INTR ; 
 int ATA_DMA_ERR ; 
 int ATA_DMA_INTR ; 
 scalar_t__ ATA_PROT_DMA ; 
#define  HSM_ST 130 
 int HSM_ST_ERR ; 
#define  HSM_ST_FIRST 129 
#define  HSM_ST_LAST 128 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  VPRINTK (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ata_ehi_push_desc (struct ata_eh_info*,char*,int) ; 
 int /*<<< orphan*/  ata_port_printk (struct ata_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ata_sff_hsm_move (struct ata_port*,struct ata_queued_cmd*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_queued_cmd*) ; 
 int stub3 (struct ata_port*) ; 
 int stub4 (struct ata_port*) ; 
 int /*<<< orphan*/  stub5 (struct ata_port*) ; 
 int /*<<< orphan*/  stub6 (struct ata_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int bfin_ata_host_intr(struct ata_port *ap,
				   struct ata_queued_cmd *qc)
{
	struct ata_eh_info *ehi = &ap->link.eh_info;
	u8 status, host_stat = 0;

	VPRINTK("ata%u: protocol %d task_state %d\n",
		ap->print_id, qc->tf.protocol, ap->hsm_task_state);

	/* Check whether we are expecting interrupt in this state */
	switch (ap->hsm_task_state) {
	case HSM_ST_FIRST:
		/* Some pre-ATAPI-4 devices assert INTRQ
		 * at this state when ready to receive CDB.
		 */

		/* Check the ATA_DFLAG_CDB_INTR flag is enough here.
		 * The flag was turned on only for atapi devices.
		 * No need to check is_atapi_taskfile(&qc->tf) again.
		 */
		if (!(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			goto idle_irq;
		break;
	case HSM_ST_LAST:
		if (qc->tf.protocol == ATA_PROT_DMA ||
		    qc->tf.protocol == ATAPI_PROT_DMA) {
			/* check status of DMA engine */
			host_stat = ap->ops->bmdma_status(ap);
			VPRINTK("ata%u: host_stat 0x%X\n",
				ap->print_id, host_stat);

			/* if it's not our irq... */
			if (!(host_stat & ATA_DMA_INTR))
				goto idle_irq;

			/* before we do anything else, clear DMA-Start bit */
			ap->ops->bmdma_stop(qc);

			if (unlikely(host_stat & ATA_DMA_ERR)) {
				/* error when transfering data to/from memory */
				qc->err_mask |= AC_ERR_HOST_BUS;
				ap->hsm_task_state = HSM_ST_ERR;
			}
		}
		break;
	case HSM_ST:
		break;
	default:
		goto idle_irq;
	}

	/* check altstatus */
	status = ap->ops->sff_check_altstatus(ap);
	if (status & ATA_BUSY)
		goto busy_ata;

	/* check main status, clearing INTRQ */
	status = ap->ops->sff_check_status(ap);
	if (unlikely(status & ATA_BUSY))
		goto busy_ata;

	/* ack bmdma irq events */
	ap->ops->sff_irq_clear(ap);

	ata_sff_hsm_move(ap, qc, status, 0);

	if (unlikely(qc->err_mask) && (qc->tf.protocol == ATA_PROT_DMA ||
				       qc->tf.protocol == ATAPI_PROT_DMA))
		ata_ehi_push_desc(ehi, "BMDMA stat 0x%x", host_stat);

busy_ata:
	return 1;	/* irq handled */

idle_irq:
	ap->stats.idle_irq++;

#ifdef ATA_IRQ_TRAP
	if ((ap->stats.idle_irq % 1000) == 0) {
		ap->ops->irq_ack(ap, 0); /* debug trap */
		ata_port_printk(ap, KERN_WARNING, "irq trap\n");
		return 1;
	}
#endif
	return 0;	/* irq not handled */
}