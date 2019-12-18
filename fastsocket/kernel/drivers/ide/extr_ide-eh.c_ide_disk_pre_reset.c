#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* id; int special_flags; scalar_t__ mult_count; int dev_flags; scalar_t__ mult_req; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_CFS_ENABLE_2 ; 
 int IDE_DFLAG_KEEP_SETTINGS ; 
 int IDE_DFLAG_PARKED ; 
 int IDE_DFLAG_USING_DMA ; 
 int IDE_SFLAG_RECALIBRATE ; 
 int IDE_SFLAG_SET_GEOMETRY ; 
 int IDE_SFLAG_SET_MULTMODE ; 

__attribute__((used)) static void ide_disk_pre_reset(ide_drive_t *drive)
{
	int legacy = (drive->id[ATA_ID_CFS_ENABLE_2] & 0x0400) ? 0 : 1;

	drive->special_flags =
		legacy ? (IDE_SFLAG_SET_GEOMETRY | IDE_SFLAG_RECALIBRATE) : 0;

	drive->mult_count = 0;
	drive->dev_flags &= ~IDE_DFLAG_PARKED;

	if ((drive->dev_flags & IDE_DFLAG_KEEP_SETTINGS) == 0 &&
	    (drive->dev_flags & IDE_DFLAG_USING_DMA) == 0)
		drive->mult_req = 0;

	if (drive->mult_req != drive->mult_count)
		drive->special_flags |= IDE_SFLAG_SET_MULTMODE;
}