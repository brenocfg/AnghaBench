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
struct ata_device {TYPE_3__* link; } ;
struct TYPE_6__ {TYPE_2__* ap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * bmdma_addr; } ;
struct TYPE_5__ {TYPE_1__ ioaddr; } ;

/* Variables and functions */
 unsigned long ATA_MASK_MWDMA ; 
 unsigned long ATA_MASK_UDMA ; 

unsigned long ata_bmdma_mode_filter(struct ata_device *adev,
				    unsigned long xfer_mask)
{
	/* Filter out DMA modes if the device has been configured by
	   the BIOS as PIO only */

	if (adev->link->ap->ioaddr.bmdma_addr == NULL)
		xfer_mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);
	return xfer_mask;
}