#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {scalar_t__ dma_base; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int scc_dma_sff_read_status (TYPE_1__*) ; 
 int scc_ide_inb (scalar_t__) ; 
 int /*<<< orphan*/  scc_ide_outb (int,scalar_t__) ; 

__attribute__((used)) static int __scc_dma_end(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	u8 dma_stat, dma_cmd;

	/* get DMA command mode */
	dma_cmd = scc_ide_inb(hwif->dma_base);
	/* stop DMA */
	scc_ide_outb(dma_cmd & ~1, hwif->dma_base);
	/* get DMA status */
	dma_stat = scc_dma_sff_read_status(hwif);
	/* clear the INTR & ERROR bits */
	scc_ide_outb(dma_stat | 6, hwif->dma_base + 4);
	/* verify good DMA status */
	return (dma_stat & 7) != 4 ? (0x10 | dma_stat) : 0;
}