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
struct zram {scalar_t__ queue; scalar_t__ disk; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  del_gendisk (scalar_t__) ; 
 TYPE_1__* disk_to_dev (scalar_t__) ; 
 int /*<<< orphan*/  put_disk (scalar_t__) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zram_disk_attr_group ; 

__attribute__((used)) static void destroy_device(struct zram *zram)
{
	sysfs_remove_group(&disk_to_dev(zram->disk)->kobj,
			&zram_disk_attr_group);

	if (zram->disk) {
		del_gendisk(zram->disk);
		put_disk(zram->disk);
	}

	if (zram->queue)
		blk_cleanup_queue(zram->queue);
}