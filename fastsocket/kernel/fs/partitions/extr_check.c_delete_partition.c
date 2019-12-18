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
struct hd_struct {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  holder_dir; } ;
struct gendisk {struct disk_part_tbl* part_tbl; } ;
struct disk_part_tbl {int len; struct hd_struct* last_lookup; struct hd_struct** part; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_free_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_partition_rcu_cb ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_devt (struct hd_struct*) ; 
 int /*<<< orphan*/  part_to_dev (struct hd_struct*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct hd_struct*,int /*<<< orphan*/ *) ; 

void delete_partition(struct gendisk *disk, int partno)
{
	struct disk_part_tbl *ptbl = disk->part_tbl;
	struct hd_struct *part;

	if (partno >= ptbl->len)
		return;

	part = ptbl->part[partno];
	if (!part)
		return;

	rcu_assign_pointer(ptbl->part[partno], NULL);
	rcu_assign_pointer(ptbl->last_lookup, NULL);
	kobject_put(part->holder_dir);
	device_del(part_to_dev(part));
	blk_free_devt(part_devt(part));

	call_rcu(&part->rcu_head, delete_partition_rcu_cb);
}