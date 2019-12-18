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
typedef  int /*<<< orphan*/  u64 ;
struct device {int /*<<< orphan*/ * dma_mask; } ;
struct TYPE_5__ {scalar_t__ media; scalar_t__ queue; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_ANY ; 
 int /*<<< orphan*/  BLK_BOUNCE_HIGH ; 
 int /*<<< orphan*/  PCI_DMA_BUS_IS_PHYS ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_disk ; 

void ide_toggle_bounce(ide_drive_t *drive, int on)
{
	u64 addr = BLK_BOUNCE_HIGH;	/* dma64_addr_t */

	if (!PCI_DMA_BUS_IS_PHYS) {
		addr = BLK_BOUNCE_ANY;
	} else if (on && drive->media == ide_disk) {
		struct device *dev = drive->hwif->dev;

		if (dev && dev->dma_mask)
			addr = *dev->dma_mask;
	}

	if (drive->queue)
		blk_queue_bounce_limit(drive->queue, addr);
}