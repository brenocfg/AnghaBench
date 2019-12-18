#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_10__ {TYPE_1__* dma_ops; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_11__ {int dev_flags; int /*<<< orphan*/  name; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* dma_host_set ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 int IDE_DFLAG_USING_DMA ; 
 int XFER_MW_DMA_0 ; 
 int XFER_MW_DMA_1 ; 
 int XFER_MW_DMA_2 ; 
 int XFER_UDMA_0 ; 
 int XFER_UDMA_1 ; 
 int XFER_UDMA_2 ; 
 int /*<<< orphan*/  ide_dma_off_quietly (TYPE_3__*) ; 
 scalar_t__ ide_set_dma_mode (TYPE_3__*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc1200_tunepio (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 

__attribute__((used)) static void sc1200_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	ide_hwif_t	*hwif = drive->hwif;
	int		mode = -1;

	/*
	 * bad abuse of ->set_pio_mode interface
	 */
	switch (pio) {
		case 200: mode = XFER_UDMA_0;	break;
		case 201: mode = XFER_UDMA_1;	break;
		case 202: mode = XFER_UDMA_2;	break;
		case 100: mode = XFER_MW_DMA_0;	break;
		case 101: mode = XFER_MW_DMA_1;	break;
		case 102: mode = XFER_MW_DMA_2;	break;
	}
	if (mode != -1) {
		printk("SC1200: %s: changing (U)DMA mode\n", drive->name);
		ide_dma_off_quietly(drive);
		if (ide_set_dma_mode(drive, mode) == 0 &&
		    (drive->dev_flags & IDE_DFLAG_USING_DMA))
			hwif->dma_ops->dma_host_set(drive, 1);
		return;
	}

	sc1200_tunepio(drive, pio);
}