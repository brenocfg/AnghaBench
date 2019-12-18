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
struct the_nilfs {int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/ * ns_gc_inodes_h; int /*<<< orphan*/  ns_last_segment_lock; int /*<<< orphan*/  ns_supers; int /*<<< orphan*/  ns_list; int /*<<< orphan*/  ns_writer_sem; int /*<<< orphan*/  ns_mount_mutex; int /*<<< orphan*/  ns_super_sem; int /*<<< orphan*/  ns_sem; int /*<<< orphan*/  ns_ndirtyblks; int /*<<< orphan*/  ns_count; struct block_device* ns_bdev; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct the_nilfs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct the_nilfs *alloc_nilfs(struct block_device *bdev)
{
	struct the_nilfs *nilfs;

	nilfs = kzalloc(sizeof(*nilfs), GFP_KERNEL);
	if (!nilfs)
		return NULL;

	nilfs->ns_bdev = bdev;
	atomic_set(&nilfs->ns_count, 1);
	atomic_set(&nilfs->ns_ndirtyblks, 0);
	init_rwsem(&nilfs->ns_sem);
	init_rwsem(&nilfs->ns_super_sem);
	mutex_init(&nilfs->ns_mount_mutex);
	init_rwsem(&nilfs->ns_writer_sem);
	INIT_LIST_HEAD(&nilfs->ns_list);
	INIT_LIST_HEAD(&nilfs->ns_supers);
	spin_lock_init(&nilfs->ns_last_segment_lock);
	nilfs->ns_gc_inodes_h = NULL;
	init_rwsem(&nilfs->ns_segctor_sem);

	return nilfs;
}