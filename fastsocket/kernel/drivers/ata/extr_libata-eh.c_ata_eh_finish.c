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
struct ata_queued_cmd {int flags; int /*<<< orphan*/  result_tf; scalar_t__ err_mask; } ;
struct ata_port {scalar_t__ nr_active_links; } ;

/* Variables and functions */
 int ATA_MAX_QUEUE ; 
 int ATA_QCFLAG_FAILED ; 
 int ATA_QCFLAG_RETRY ; 
 int ATA_QCFLAG_SENSE_VALID ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 struct ata_queued_cmd* __ata_qc_from_tag (struct ata_port*,int) ; 
 int /*<<< orphan*/  ata_eh_qc_complete (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_eh_qc_retry (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ata_eh_finish(struct ata_port *ap)
{
	int tag;

	/* retry or finish qcs */
	for (tag = 0; tag < ATA_MAX_QUEUE; tag++) {
		struct ata_queued_cmd *qc = __ata_qc_from_tag(ap, tag);

		if (!(qc->flags & ATA_QCFLAG_FAILED))
			continue;

		if (qc->err_mask) {
			/* FIXME: Once EH migration is complete,
			 * generate sense data in this function,
			 * considering both err_mask and tf.
			 */
			if (qc->flags & ATA_QCFLAG_RETRY)
				ata_eh_qc_retry(qc);
			else
				ata_eh_qc_complete(qc);
		} else {
			if (qc->flags & ATA_QCFLAG_SENSE_VALID) {
				ata_eh_qc_complete(qc);
			} else {
				/* feed zero TF to sense generation */
				memset(&qc->result_tf, 0, sizeof(qc->result_tf));
				ata_eh_qc_retry(qc);
			}
		}
	}

	/* make sure nr_active_links is zero after EH */
	WARN_ON(ap->nr_active_links);
	ap->nr_active_links = 0;
}