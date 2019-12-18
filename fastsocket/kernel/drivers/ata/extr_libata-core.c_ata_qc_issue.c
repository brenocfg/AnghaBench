#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {int tag; int err_mask; TYPE_2__* dev; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  n_elem; int /*<<< orphan*/  sg; int /*<<< orphan*/  flags; TYPE_1__ tf; struct ata_port* ap; } ;
struct ata_port {int qc_active; int flags; TYPE_3__* ops; int /*<<< orphan*/  nr_active_links; } ;
struct TYPE_8__ {int /*<<< orphan*/  action; } ;
struct ata_link {int active_tag; int sactive; TYPE_4__ eh_info; } ;
struct TYPE_7__ {int (* qc_issue ) (struct ata_queued_cmd*) ;int /*<<< orphan*/  (* qc_prep ) (struct ata_queued_cmd*) ;scalar_t__ error_handler; } ;
struct TYPE_6__ {int flags; struct ata_link* link; } ;

/* Variables and functions */
 int AC_ERR_SYSTEM ; 
 int ATA_DFLAG_SLEEPING ; 
 int /*<<< orphan*/  ATA_EH_RESET ; 
 int ATA_FLAG_PIO_DMA ; 
 int /*<<< orphan*/  ATA_QCFLAG_ACTIVE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ata_ehi_push_desc (TYPE_4__*,char*) ; 
 scalar_t__ ata_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_is_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_is_ncq (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_is_pio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_link_abort (struct ata_link*) ; 
 int /*<<< orphan*/  ata_qc_complete (struct ata_queued_cmd*) ; 
 scalar_t__ ata_sg_setup (struct ata_queued_cmd*) ; 
 scalar_t__ ata_tag_valid (int) ; 
 int /*<<< orphan*/  stub1 (struct ata_queued_cmd*) ; 
 int stub2 (struct ata_queued_cmd*) ; 
 scalar_t__ unlikely (int) ; 

void ata_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_link *link = qc->dev->link;
	u8 prot = qc->tf.protocol;

	/* Make sure only one non-NCQ command is outstanding.  The
	 * check is skipped for old EH because it reuses active qc to
	 * request ATAPI sense.
	 */
	WARN_ON_ONCE(ap->ops->error_handler && ata_tag_valid(link->active_tag));

	if (ata_is_ncq(prot)) {
		WARN_ON_ONCE(link->sactive & (1 << qc->tag));

		if (!link->sactive)
			ap->nr_active_links++;
		link->sactive |= 1 << qc->tag;
	} else {
		WARN_ON_ONCE(link->sactive);

		ap->nr_active_links++;
		link->active_tag = qc->tag;
	}

	qc->flags |= ATA_QCFLAG_ACTIVE;
	ap->qc_active |= 1 << qc->tag;

	/* We guarantee to LLDs that they will have at least one
	 * non-zero sg if the command is a data command.
	 */
	BUG_ON(ata_is_data(prot) && (!qc->sg || !qc->n_elem || !qc->nbytes));

	if (ata_is_dma(prot) || (ata_is_pio(prot) &&
				 (ap->flags & ATA_FLAG_PIO_DMA)))
		if (ata_sg_setup(qc))
			goto sg_err;

	/* if device is sleeping, schedule reset and abort the link */
	if (unlikely(qc->dev->flags & ATA_DFLAG_SLEEPING)) {
		link->eh_info.action |= ATA_EH_RESET;
		ata_ehi_push_desc(&link->eh_info, "waking up from sleep");
		ata_link_abort(link);
		return;
	}

	ap->ops->qc_prep(qc);

	qc->err_mask |= ap->ops->qc_issue(qc);
	if (unlikely(qc->err_mask))
		goto err;
	return;

sg_err:
	qc->err_mask |= AC_ERR_SYSTEM;
err:
	ata_qc_complete(qc);
}