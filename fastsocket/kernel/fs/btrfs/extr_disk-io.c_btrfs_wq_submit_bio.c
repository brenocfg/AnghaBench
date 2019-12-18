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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  nr_async_submits; int /*<<< orphan*/  async_submit_wait; int /*<<< orphan*/  async_submit_draining; int /*<<< orphan*/  workers; } ;
struct bio {int dummy; } ;
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/  ordered_free; int /*<<< orphan*/  ordered_func; int /*<<< orphan*/  func; } ;
struct async_submit_bio {int rw; int mirror_num; unsigned long bio_flags; TYPE_1__ work; scalar_t__ error; int /*<<< orphan*/  bio_offset; int /*<<< orphan*/ * submit_bio_done; int /*<<< orphan*/ * submit_bio_start; struct bio* bio; struct inode* inode; } ;
typedef  int /*<<< orphan*/  extent_submit_bio_hook_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_queue_worker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  btrfs_set_work_high_prio (TYPE_1__*) ; 
 struct async_submit_bio* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_one_async_done ; 
 int /*<<< orphan*/  run_one_async_free ; 
 int /*<<< orphan*/  run_one_async_start ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int btrfs_wq_submit_bio(struct btrfs_fs_info *fs_info, struct inode *inode,
			int rw, struct bio *bio, int mirror_num,
			unsigned long bio_flags,
			u64 bio_offset,
			extent_submit_bio_hook_t *submit_bio_start,
			extent_submit_bio_hook_t *submit_bio_done)
{
	struct async_submit_bio *async;

	async = kmalloc(sizeof(*async), GFP_NOFS);
	if (!async)
		return -ENOMEM;

	async->inode = inode;
	async->rw = rw;
	async->bio = bio;
	async->mirror_num = mirror_num;
	async->submit_bio_start = submit_bio_start;
	async->submit_bio_done = submit_bio_done;

	async->work.func = run_one_async_start;
	async->work.ordered_func = run_one_async_done;
	async->work.ordered_free = run_one_async_free;

	async->work.flags = 0;
	async->bio_flags = bio_flags;
	async->bio_offset = bio_offset;

	async->error = 0;

	atomic_inc(&fs_info->nr_async_submits);

	if (rw & REQ_SYNC)
		btrfs_set_work_high_prio(&async->work);

	btrfs_queue_worker(&fs_info->workers, &async->work);

	while (atomic_read(&fs_info->async_submit_draining) &&
	      atomic_read(&fs_info->nr_async_submits)) {
		wait_event(fs_info->async_submit_wait,
			   (atomic_read(&fs_info->nr_async_submits) == 0));
	}

	return 0;
}