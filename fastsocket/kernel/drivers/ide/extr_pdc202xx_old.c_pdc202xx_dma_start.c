#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct request {int dummy; } ;
struct TYPE_6__ {int extra_base; scalar_t__ channel; struct request* rq; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {scalar_t__ current_speed; scalar_t__ media; int dev_flags; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_DFLAG_LBA48 ; 
 scalar_t__ READ ; 
 scalar_t__ XFER_UDMA_2 ; 
 int blk_rq_sectors (struct request*) ; 
 scalar_t__ ide_disk ; 
 int /*<<< orphan*/  ide_dma_start (TYPE_2__*) ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 
 int /*<<< orphan*/  pdc_old_enable_66MHz_clock (TYPE_1__*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static void pdc202xx_dma_start(ide_drive_t *drive)
{
	if (drive->current_speed > XFER_UDMA_2)
		pdc_old_enable_66MHz_clock(drive->hwif);
	if (drive->media != ide_disk || (drive->dev_flags & IDE_DFLAG_LBA48)) {
		ide_hwif_t *hwif	= drive->hwif;
		struct request *rq	= hwif->rq;
		unsigned long high_16	= hwif->extra_base - 16;
		unsigned long atapi_reg	= high_16 + (hwif->channel ? 0x24 : 0x20);
		u32 word_count	= 0;
		u8 clock = inb(high_16 + 0x11);

		outb(clock | (hwif->channel ? 0x08 : 0x02), high_16 + 0x11);
		word_count = (blk_rq_sectors(rq) << 8);
		word_count = (rq_data_dir(rq) == READ) ?
					word_count | 0x05000000 :
					word_count | 0x06000000;
		outl(word_count, atapi_reg);
	}
	ide_dma_start(drive);
}