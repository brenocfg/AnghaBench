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
typedef  int u8 ;
struct TYPE_6__ {unsigned int flags; } ;
struct ata_queued_cmd {TYPE_3__ tf; struct ata_port* ap; } ;
struct TYPE_4__ {scalar_t__ bmdma_addr; } ;
struct ata_port {TYPE_2__* ops; TYPE_1__ ioaddr; int /*<<< orphan*/  prd_dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* sff_exec_command ) (struct ata_port*,TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ ATA_DMA_CMD ; 
 int ATA_DMA_ERR ; 
 int ATA_DMA_INTR ; 
 int ATA_DMA_START ; 
 scalar_t__ ATA_DMA_TABLE_OFS ; 
 int ATA_DMA_WR ; 
 unsigned int ATA_TFLAG_WRITE ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,TYPE_3__*) ; 

__attribute__((used)) static void ns87415_bmdma_setup(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	unsigned int rw = (qc->tf.flags & ATA_TFLAG_WRITE);
	u8 dmactl;

	/* load PRD table addr. */
	mb();	/* make sure PRD table writes are visible to controller */
	iowrite32(ap->prd_dma, ap->ioaddr.bmdma_addr + ATA_DMA_TABLE_OFS);

	/* specify data direction, triple-check start bit is clear */
	dmactl = ioread8(ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
	dmactl &= ~(ATA_DMA_WR | ATA_DMA_START);
	/* Due to an erratum we need to write these bits to the wrong
	   place - which does save us an I/O bizarrely */
	dmactl |= ATA_DMA_INTR | ATA_DMA_ERR;
	if (!rw)
		dmactl |= ATA_DMA_WR;
	iowrite8(dmactl, ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
	/* issue r/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
}