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
struct TYPE_2__ {int protocol; } ;
struct ata_queued_cmd {TYPE_1__ tf; } ;

/* Variables and functions */
#define  ATA_PROT_DMA 129 
#define  ATA_PROT_NODATA 128 
 int /*<<< orphan*/  pdc20621_dma_prep (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  pdc20621_nodata_prep (struct ata_queued_cmd*) ; 

__attribute__((used)) static void pdc20621_qc_prep(struct ata_queued_cmd *qc)
{
	switch (qc->tf.protocol) {
	case ATA_PROT_DMA:
		pdc20621_dma_prep(qc);
		break;
	case ATA_PROT_NODATA:
		pdc20621_nodata_prep(qc);
		break;
	default:
		break;
	}
}