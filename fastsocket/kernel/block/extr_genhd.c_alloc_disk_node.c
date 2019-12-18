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
struct gendisk {int node_id; int minors; int /*<<< orphan*/  async_notify; int /*<<< orphan*/  part0; TYPE_1__* part_tbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * class; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** part; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  block_class ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 scalar_t__ disk_expand_part_tbl (struct gendisk*,int /*<<< orphan*/ ) ; 
 TYPE_2__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  disk_type ; 
 int /*<<< orphan*/  free_part_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_part_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gendisk*) ; 
 struct gendisk* kmalloc_node (int,int,int) ; 
 int /*<<< orphan*/  media_change_notify_thread ; 
 int /*<<< orphan*/  rand_initialize_disk (struct gendisk*) ; 

struct gendisk *alloc_disk_node(int minors, int node_id)
{
	struct gendisk *disk;

	disk = kmalloc_node(sizeof(struct gendisk),
				GFP_KERNEL | __GFP_ZERO, node_id);
	if (disk) {
		if (!init_part_stats(&disk->part0)) {
			kfree(disk);
			return NULL;
		}
		disk->node_id = node_id;
		if (disk_expand_part_tbl(disk, 0)) {
			free_part_stats(&disk->part0);
			kfree(disk);
			return NULL;
		}
		disk->part_tbl->part[0] = &disk->part0;

		disk->minors = minors;
		rand_initialize_disk(disk);
		disk_to_dev(disk)->class = &block_class;
		disk_to_dev(disk)->type = &disk_type;
		device_initialize(disk_to_dev(disk));
		INIT_WORK(&disk->async_notify,
			media_change_notify_thread);
	}
	return disk;
}