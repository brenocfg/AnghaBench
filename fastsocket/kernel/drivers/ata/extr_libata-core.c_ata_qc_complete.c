#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int command; int /*<<< orphan*/  feature; } ;
struct ata_queued_cmd {int err_mask; int flags; TYPE_3__ tf; int /*<<< orphan*/  tag; struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {int pflags; TYPE_1__* ops; } ;
struct ata_eh_info {int /*<<< orphan*/ * dev_action; } ;
struct ata_device {size_t devno; int flags; TYPE_2__* link; } ;
struct TYPE_5__ {struct ata_eh_info eh_info; } ;
struct TYPE_4__ {scalar_t__ error_handler; } ;

/* Variables and functions */
#define  ATA_CMD_INIT_DEV_PARAMS 131 
#define  ATA_CMD_SET_FEATURES 130 
#define  ATA_CMD_SET_MULTI 129 
#define  ATA_CMD_SLEEP 128 
 int ATA_DFLAG_DUBIOUS_XFER ; 
 int ATA_DFLAG_SLEEPING ; 
 int /*<<< orphan*/  ATA_EH_REVALIDATE ; 
 int ATA_PFLAG_FROZEN ; 
 int ATA_QCFLAG_EH_SCHEDULED ; 
 int ATA_QCFLAG_FAILED ; 
 int ATA_QCFLAG_RESULT_TF ; 
 int /*<<< orphan*/  SETFEATURES_WC_OFF ; 
 int /*<<< orphan*/  SETFEATURES_WC_ON ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __ata_qc_complete (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_port_schedule_eh (struct ata_port*) ; 
 int /*<<< orphan*/  ata_qc_schedule_eh (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_tag_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_verify_xfer (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  fill_result_tf (struct ata_queued_cmd*) ; 
 scalar_t__ unlikely (int) ; 

void ata_qc_complete(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;

	/* XXX: New EH and old EH use different mechanisms to
	 * synchronize EH with regular execution path.
	 *
	 * In new EH, a failed qc is marked with ATA_QCFLAG_FAILED.
	 * Normal execution path is responsible for not accessing a
	 * failed qc.  libata core enforces the rule by returning NULL
	 * from ata_qc_from_tag() for failed qcs.
	 *
	 * Old EH depends on ata_qc_complete() nullifying completion
	 * requests if ATA_QCFLAG_EH_SCHEDULED is set.  Old EH does
	 * not synchronize with interrupt handler.  Only PIO task is
	 * taken care of.
	 */
	if (ap->ops->error_handler) {
		struct ata_device *dev = qc->dev;
		struct ata_eh_info *ehi = &dev->link->eh_info;

		if (unlikely(qc->err_mask))
			qc->flags |= ATA_QCFLAG_FAILED;

		if (unlikely(qc->flags & ATA_QCFLAG_FAILED)) {
			/* always fill result TF for failed qc */
			fill_result_tf(qc);

			if (!ata_tag_internal(qc->tag))
				ata_qc_schedule_eh(qc);
			else
				__ata_qc_complete(qc);
			return;
		}

		WARN_ON_ONCE(ap->pflags & ATA_PFLAG_FROZEN);

		/* read result TF if requested */
		if (qc->flags & ATA_QCFLAG_RESULT_TF)
			fill_result_tf(qc);

		/* Some commands need post-processing after successful
		 * completion.
		 */
		switch (qc->tf.command) {
		case ATA_CMD_SET_FEATURES:
			if (qc->tf.feature != SETFEATURES_WC_ON &&
			    qc->tf.feature != SETFEATURES_WC_OFF)
				break;
			/* fall through */
		case ATA_CMD_INIT_DEV_PARAMS: /* CHS translation changed */
		case ATA_CMD_SET_MULTI: /* multi_count changed */
			/* revalidate device */
			ehi->dev_action[dev->devno] |= ATA_EH_REVALIDATE;
			ata_port_schedule_eh(ap);
			break;

		case ATA_CMD_SLEEP:
			dev->flags |= ATA_DFLAG_SLEEPING;
			break;
		}

		if (unlikely(dev->flags & ATA_DFLAG_DUBIOUS_XFER))
			ata_verify_xfer(qc);

		__ata_qc_complete(qc);
	} else {
		if (qc->flags & ATA_QCFLAG_EH_SCHEDULED)
			return;

		/* read result TF if failed or requested */
		if (qc->err_mask || qc->flags & ATA_QCFLAG_RESULT_TF)
			fill_result_tf(qc);

		__ata_qc_complete(qc);
	}
}