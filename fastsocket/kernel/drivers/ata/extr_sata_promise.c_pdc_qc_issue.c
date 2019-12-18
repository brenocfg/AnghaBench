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
struct ata_queued_cmd {TYPE_2__ tf; TYPE_1__* dev; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
#define  ATAPI_PROT_DMA 131 
#define  ATAPI_PROT_NODATA 130 
 int ATA_DFLAG_CDB_INTR ; 
#define  ATA_PROT_DMA 129 
#define  ATA_PROT_NODATA 128 
 int ATA_TFLAG_POLLING ; 
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  pdc_packet_start (struct ata_queued_cmd*) ; 

__attribute__((used)) static unsigned int pdc_qc_issue(struct ata_queued_cmd *qc)
{
	switch (qc->tf.protocol) {
	case ATAPI_PROT_NODATA:
		if (qc->dev->flags & ATA_DFLAG_CDB_INTR)
			break;
		/*FALLTHROUGH*/
	case ATA_PROT_NODATA:
		if (qc->tf.flags & ATA_TFLAG_POLLING)
			break;
		/*FALLTHROUGH*/
	case ATAPI_PROT_DMA:
	case ATA_PROT_DMA:
		pdc_packet_start(qc);
		return 0;
	default:
		break;
	}
	return ata_sff_qc_issue(qc);
}