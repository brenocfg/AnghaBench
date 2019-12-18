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
typedef  int u16 ;
struct TYPE_5__ {int host_flags; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int* id; scalar_t__ media; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_FIELD_VALID ; 
 size_t ATA_ID_MWDMA_MODES ; 
 size_t ATA_ID_SWDMA_MODES ; 
 size_t ATA_ID_UDMA_MODES ; 
 int IDE_HFLAG_NO_ATAPI_DMA ; 
 scalar_t__ ide_disk ; 
 scalar_t__ ide_dma_good_drive (TYPE_2__*) ; 

int config_drive_for_dma(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	u16 *id = drive->id;

	if (drive->media != ide_disk) {
		if (hwif->host_flags & IDE_HFLAG_NO_ATAPI_DMA)
			return 0;
	}

	/*
	 * Enable DMA on any drive that has
	 * UltraDMA (mode 0/1/2/3/4/5/6) enabled
	 */
	if ((id[ATA_ID_FIELD_VALID] & 4) &&
	    ((id[ATA_ID_UDMA_MODES] >> 8) & 0x7f))
		return 1;

	/*
	 * Enable DMA on any drive that has mode2 DMA
	 * (multi or single) enabled
	 */
	if ((id[ATA_ID_MWDMA_MODES] & 0x404) == 0x404 ||
	    (id[ATA_ID_SWDMA_MODES] & 0x404) == 0x404)
		return 1;

	/* Consult the list of known "good" drives */
	if (ide_dma_good_drive(drive))
		return 1;

	return 0;
}