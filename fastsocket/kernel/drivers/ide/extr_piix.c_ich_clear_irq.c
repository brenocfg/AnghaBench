#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ dma_base; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {scalar_t__ waiting_for_dma; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATA_DMA_STATUS ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ich_clear_irq(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	u8 dma_stat;

	/*
	 * ide_dma_end() needs BMDMA status for error checking.
	 * So, skip clearing BMDMA status here and leave it
	 * to ide_dma_end() if this is DMA interrupt.
	 */
	if (drive->waiting_for_dma || hwif->dma_base == 0)
		return;

	/* clear the INTR & ERROR bits */
	dma_stat = inb(hwif->dma_base + ATA_DMA_STATUS);
	/* Should we force the bit as well ? */
	outb(dma_stat, hwif->dma_base + ATA_DMA_STATUS);
}