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
struct gendisk {unsigned int first_minor; int /*<<< orphan*/  queue; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  major; } ;
struct TYPE_4__ {char index; int /*<<< orphan*/  major; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dn; int /*<<< orphan*/  queue; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 char MAX_DRIVES ; 
 unsigned int PARTN_BITS ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char) ; 

void ide_init_disk(struct gendisk *disk, ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	unsigned int unit = drive->dn & 1;

	disk->major = hwif->major;
	disk->first_minor = unit << PARTN_BITS;
	sprintf(disk->disk_name, "hd%c", 'a' + hwif->index * MAX_DRIVES + unit);
	disk->queue = drive->queue;
}