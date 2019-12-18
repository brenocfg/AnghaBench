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
struct ata_queued_cmd {unsigned int tag; } ;
struct ata_port {int pflags; int /*<<< orphan*/  qc_allocated; } ;

/* Variables and functions */
 int ATA_MAX_QUEUE ; 
 int ATA_PFLAG_FROZEN ; 
 struct ata_queued_cmd* __ata_qc_from_tag (struct ata_port*,unsigned int) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ata_queued_cmd *ata_qc_new(struct ata_port *ap)
{
	struct ata_queued_cmd *qc = NULL;
	unsigned int i;

	/* no command while frozen */
	if (unlikely(ap->pflags & ATA_PFLAG_FROZEN))
		return NULL;

	/* the last tag is reserved for internal command. */
	for (i = 0; i < ATA_MAX_QUEUE - 1; i++)
		if (!test_and_set_bit(i, &ap->qc_allocated)) {
			qc = __ata_qc_from_tag(ap, i);
			break;
		}

	if (qc)
		qc->tag = i;

	return qc;
}