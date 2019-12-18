#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pdc_port_priv {int /*<<< orphan*/  pkt; } ;
struct TYPE_9__ {int protocol; int flags; } ;
struct ata_queued_cmd {TYPE_3__ tf; TYPE_2__* dev; TYPE_1__* ap; } ;
struct TYPE_8__ {int /*<<< orphan*/  devno; } ;
struct TYPE_7__ {int /*<<< orphan*/  prd_dma; struct pdc_port_priv* private_data; } ;

/* Variables and functions */
#define  ATAPI_PROT_DMA 132 
#define  ATAPI_PROT_NODATA 131 
#define  ATAPI_PROT_PIO 130 
#define  ATA_PROT_DMA 129 
#define  ATA_PROT_NODATA 128 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 int /*<<< orphan*/  pdc_atapi_pkt (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  pdc_fill_sg (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  pdc_pkt_footer (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int pdc_pkt_header (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int pdc_prep_lba28 (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int pdc_prep_lba48 (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void pdc_qc_prep(struct ata_queued_cmd *qc)
{
	struct pdc_port_priv *pp = qc->ap->private_data;
	unsigned int i;

	VPRINTK("ENTER\n");

	switch (qc->tf.protocol) {
	case ATA_PROT_DMA:
		pdc_fill_sg(qc);
		/*FALLTHROUGH*/
	case ATA_PROT_NODATA:
		i = pdc_pkt_header(&qc->tf, qc->ap->prd_dma,
				   qc->dev->devno, pp->pkt);
		if (qc->tf.flags & ATA_TFLAG_LBA48)
			i = pdc_prep_lba48(&qc->tf, pp->pkt, i);
		else
			i = pdc_prep_lba28(&qc->tf, pp->pkt, i);
		pdc_pkt_footer(&qc->tf, pp->pkt, i);
		break;
	case ATAPI_PROT_PIO:
		pdc_fill_sg(qc);
		break;
	case ATAPI_PROT_DMA:
		pdc_fill_sg(qc);
		/*FALLTHROUGH*/
	case ATAPI_PROT_NODATA:
		pdc_atapi_pkt(qc);
		break;
	default:
		break;
	}
}