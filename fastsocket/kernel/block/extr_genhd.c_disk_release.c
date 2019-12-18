#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gendisk {scalar_t__ queue; int /*<<< orphan*/  part0; struct gendisk* random; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_put_queue (scalar_t__) ; 
 struct gendisk* dev_to_disk (struct device*) ; 
 int /*<<< orphan*/  disk_replace_part_tbl (struct gendisk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_part_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gendisk*) ; 

__attribute__((used)) static void disk_release(struct device *dev)
{
	struct gendisk *disk = dev_to_disk(dev);

	kfree(disk->random);
	disk_replace_part_tbl(disk, NULL);
	free_part_stats(&disk->part0);
	if (disk->queue)
		blk_put_queue(disk->queue);
	kfree(disk);
}