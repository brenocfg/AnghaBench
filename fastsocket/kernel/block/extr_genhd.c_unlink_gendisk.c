#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gendisk {int /*<<< orphan*/  minors; TYPE_1__* queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdi_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_unregister_queue (struct gendisk*) ; 
 int /*<<< orphan*/  blk_unregister_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_devt (struct gendisk*) ; 
 TYPE_2__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void unlink_gendisk(struct gendisk *disk)
{
	sysfs_remove_link(&disk_to_dev(disk)->kobj, "bdi");
	bdi_unregister(&disk->queue->backing_dev_info);
	blk_unregister_queue(disk);
	blk_unregister_region(disk_devt(disk), disk->minors);
}