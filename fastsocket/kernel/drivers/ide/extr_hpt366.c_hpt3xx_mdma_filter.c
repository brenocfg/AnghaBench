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
typedef  int u8 ;
struct hpt_info {int chip_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int /*<<< orphan*/  id; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
#define  HPT372 131 
#define  HPT372A 130 
#define  HPT372N 129 
#define  HPT374 128 
 int /*<<< orphan*/  ata_id_is_sata (int /*<<< orphan*/ ) ; 
 struct hpt_info* hpt3xx_get_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 hpt3xx_mdma_filter(ide_drive_t *drive)
{
	ide_hwif_t *hwif	= drive->hwif;
	struct hpt_info *info	= hpt3xx_get_info(hwif->dev);

	switch (info->chip_type) {
	case HPT372 :
	case HPT372A:
	case HPT372N:
	case HPT374 :
		if (ata_id_is_sata(drive->id))
			return 0x00;
		/* Fall thru */
	default:
		return 0x07;
	}
}