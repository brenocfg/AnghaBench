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
struct ata_queued_cmd {unsigned int tag; scalar_t__ flags; struct ata_port* ap; } ;
struct ata_port {int /*<<< orphan*/  qc_allocated; } ;

/* Variables and functions */
 unsigned int ATA_TAG_POISON ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tag_valid (unsigned int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

void ata_qc_free(struct ata_queued_cmd *qc)
{
	struct ata_port *ap;
	unsigned int tag;

	WARN_ON_ONCE(qc == NULL); /* ata_qc_from_tag _might_ return NULL */
	ap = qc->ap;

	qc->flags = 0;
	tag = qc->tag;
	if (likely(ata_tag_valid(tag))) {
		qc->tag = ATA_TAG_POISON;
		clear_bit(tag, &ap->qc_allocated);
	}
}