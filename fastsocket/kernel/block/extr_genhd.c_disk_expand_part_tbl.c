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
struct gendisk {int /*<<< orphan*/  node_id; struct disk_part_tbl* part_tbl; } ;
struct disk_part_tbl {int len; int /*<<< orphan*/ * part; int /*<<< orphan*/  rcu_head; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_RCU_HEAD (int /*<<< orphan*/ *) ; 
 int disk_max_parts (struct gendisk*) ; 
 int /*<<< orphan*/  disk_replace_part_tbl (struct gendisk*,struct disk_part_tbl*) ; 
 struct disk_part_tbl* kzalloc_node (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int disk_expand_part_tbl(struct gendisk *disk, int partno)
{
	struct disk_part_tbl *old_ptbl = disk->part_tbl;
	struct disk_part_tbl *new_ptbl;
	int len = old_ptbl ? old_ptbl->len : 0;
	int target = partno + 1;
	size_t size;
	int i;

	/* disk_max_parts() is zero during initialization, ignore if so */
	if (disk_max_parts(disk) && target > disk_max_parts(disk))
		return -EINVAL;

	if (target <= len)
		return 0;

	size = sizeof(*new_ptbl) + target * sizeof(new_ptbl->part[0]);
	new_ptbl = kzalloc_node(size, GFP_KERNEL, disk->node_id);
	if (!new_ptbl)
		return -ENOMEM;

	INIT_RCU_HEAD(&new_ptbl->rcu_head);
	new_ptbl->len = target;

	for (i = 0; i < len; i++)
		rcu_assign_pointer(new_ptbl->part[i], old_ptbl->part[i]);

	disk_replace_part_tbl(disk, new_ptbl);
	return 0;
}