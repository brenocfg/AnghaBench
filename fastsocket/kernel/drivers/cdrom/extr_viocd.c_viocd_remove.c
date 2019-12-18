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
struct vio_dev {size_t unit_address; } ;
struct disk_info {TYPE_1__* viocd_disk; int /*<<< orphan*/  viocd_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_cdrom (int /*<<< orphan*/ *) ; 
 struct disk_info* viocd_diskinfo ; 

__attribute__((used)) static int viocd_remove(struct vio_dev *vdev)
{
	struct disk_info *d = &viocd_diskinfo[vdev->unit_address];

	unregister_cdrom(&d->viocd_info);
	del_gendisk(d->viocd_disk);
	blk_cleanup_queue(d->viocd_disk->queue);
	put_disk(d->viocd_disk);
	return 0;
}