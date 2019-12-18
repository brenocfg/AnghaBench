#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ide_disk_obj {TYPE_1__* drive; } ;
struct gendisk {int dummy; } ;
struct TYPE_2__ {int dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int IDE_DFLAG_ATTACH ; 
 int IDE_DFLAG_MEDIA_CHANGED ; 
 int /*<<< orphan*/  ide_disk_obj ; 
 struct ide_disk_obj* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_gd_media_changed(struct gendisk *disk)
{
	struct ide_disk_obj *idkp = ide_drv_g(disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;
	int ret;

	/* do not scan partitions twice if this is a removable device */
	if (drive->dev_flags & IDE_DFLAG_ATTACH) {
		drive->dev_flags &= ~IDE_DFLAG_ATTACH;
		return 0;
	}

	ret = !!(drive->dev_flags & IDE_DFLAG_MEDIA_CHANGED);
	drive->dev_flags &= ~IDE_DFLAG_MEDIA_CHANGED;

	return ret;
}