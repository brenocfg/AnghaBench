#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ protocol; } ;
struct ata_queued_cmd {int flags; TYPE_1__ tf; } ;

/* Variables and functions */
 scalar_t__ ATA_PROT_NCQ ; 
 int ATA_QCFLAG_DMAMAP ; 
 int /*<<< orphan*/  ata_sff_qc_prep (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  nv_swncq_fill_sg (struct ata_queued_cmd*) ; 

__attribute__((used)) static void nv_swncq_qc_prep(struct ata_queued_cmd *qc)
{
	if (qc->tf.protocol != ATA_PROT_NCQ) {
		ata_sff_qc_prep(qc);
		return;
	}

	if (!(qc->flags & ATA_QCFLAG_DMAMAP))
		return;

	nv_swncq_fill_sg(qc);
}