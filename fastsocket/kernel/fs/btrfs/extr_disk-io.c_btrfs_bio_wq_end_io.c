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
struct end_io_wq {int metadata; struct bio* bio; scalar_t__ error; struct btrfs_fs_info* info; int /*<<< orphan*/  end_io; struct end_io_wq* private; } ;
struct btrfs_fs_info {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct end_io_wq* bi_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  end_workqueue_bio ; 
 struct end_io_wq* kmalloc (int,int /*<<< orphan*/ ) ; 

int btrfs_bio_wq_end_io(struct btrfs_fs_info *info, struct bio *bio,
			int metadata)
{
	struct end_io_wq *end_io_wq;
	end_io_wq = kmalloc(sizeof(*end_io_wq), GFP_NOFS);
	if (!end_io_wq)
		return -ENOMEM;

	end_io_wq->private = bio->bi_private;
	end_io_wq->end_io = bio->bi_end_io;
	end_io_wq->info = info;
	end_io_wq->error = 0;
	end_io_wq->bio = bio;
	end_io_wq->metadata = metadata;

	bio->bi_private = end_io_wq;
	bio->bi_end_io = end_workqueue_bio;
	return 0;
}