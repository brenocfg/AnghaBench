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
struct TYPE_2__ {scalar_t__ flags; int /*<<< orphan*/  func; } ;
struct end_io_wq {int error; int metadata; TYPE_1__ work; struct btrfs_fs_info* info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  endio_workers; int /*<<< orphan*/  endio_meta_workers; int /*<<< orphan*/  endio_write_workers; int /*<<< orphan*/  endio_freespace_worker; int /*<<< orphan*/  endio_meta_write_workers; } ;
struct bio {int bi_rw; struct end_io_wq* bi_private; } ;

/* Variables and functions */
 int REQ_WRITE ; 
 int /*<<< orphan*/  btrfs_queue_worker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  end_workqueue_fn ; 

__attribute__((used)) static void end_workqueue_bio(struct bio *bio, int err)
{
	struct end_io_wq *end_io_wq = bio->bi_private;
	struct btrfs_fs_info *fs_info;

	fs_info = end_io_wq->info;
	end_io_wq->error = err;
	end_io_wq->work.func = end_workqueue_fn;
	end_io_wq->work.flags = 0;

	if (bio->bi_rw & REQ_WRITE) {
		if (end_io_wq->metadata == 1)
			btrfs_queue_worker(&fs_info->endio_meta_write_workers,
					   &end_io_wq->work);
		else if (end_io_wq->metadata == 2)
			btrfs_queue_worker(&fs_info->endio_freespace_worker,
					   &end_io_wq->work);
		else
			btrfs_queue_worker(&fs_info->endio_write_workers,
					   &end_io_wq->work);
	} else {
		if (end_io_wq->metadata)
			btrfs_queue_worker(&fs_info->endio_meta_workers,
					   &end_io_wq->work);
		else
			btrfs_queue_worker(&fs_info->endio_workers,
					   &end_io_wq->work);
	}
}