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
struct ide_disk_obj {int /*<<< orphan*/  dev; int /*<<< orphan*/  driver; struct gendisk* disk; } ;
struct gendisk {int dummy; } ;
struct TYPE_7__ {TYPE_1__* disk_ops; struct ide_disk_obj* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* flush ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_gendisk (struct gendisk*) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_disk_ref_mutex ; 
 int /*<<< orphan*/  ide_proc_unregister_driver (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void ide_gd_remove(ide_drive_t *drive)
{
	struct ide_disk_obj *idkp = drive->driver_data;
	struct gendisk *g = idkp->disk;

	ide_proc_unregister_driver(drive, idkp->driver);
	device_del(&idkp->dev);
	del_gendisk(g);
	drive->disk_ops->flush(drive);

	mutex_lock(&ide_disk_ref_mutex);
	put_device(&idkp->dev);
	mutex_unlock(&ide_disk_ref_mutex);
}