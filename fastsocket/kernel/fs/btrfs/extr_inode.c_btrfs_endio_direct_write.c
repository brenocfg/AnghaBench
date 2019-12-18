#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_5__ {scalar_t__ flags; int /*<<< orphan*/  func; } ;
struct btrfs_ordered_extent {TYPE_2__ work; } ;
struct btrfs_dio_private {scalar_t__ logical_offset; scalar_t__ bytes; struct btrfs_dio_private* private; struct inode* inode; } ;
struct bio {int /*<<< orphan*/  bi_flags; struct btrfs_dio_private* bi_private; } ;
struct TYPE_6__ {struct btrfs_root* root; } ;
struct TYPE_4__ {int /*<<< orphan*/  endio_write_workers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int btrfs_dec_test_first_ordered_pending (struct inode*,struct btrfs_ordered_extent**,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_queue_worker (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dio_end_io (struct bio*,int) ; 
 int /*<<< orphan*/  finish_ordered_fn ; 
 int /*<<< orphan*/  kfree (struct btrfs_dio_private*) ; 

__attribute__((used)) static void btrfs_endio_direct_write(struct bio *bio, int err)
{
	struct btrfs_dio_private *dip = bio->bi_private;
	struct inode *inode = dip->inode;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_ordered_extent *ordered = NULL;
	u64 ordered_offset = dip->logical_offset;
	u64 ordered_bytes = dip->bytes;
	int ret;

	if (err)
		goto out_done;
again:
	ret = btrfs_dec_test_first_ordered_pending(inode, &ordered,
						   &ordered_offset,
						   ordered_bytes, !err);
	if (!ret)
		goto out_test;

	ordered->work.func = finish_ordered_fn;
	ordered->work.flags = 0;
	btrfs_queue_worker(&root->fs_info->endio_write_workers,
			   &ordered->work);
out_test:
	/*
	 * our bio might span multiple ordered extents.  If we haven't
	 * completed the accounting for the whole dio, go back and try again
	 */
	if (ordered_offset < dip->logical_offset + dip->bytes) {
		ordered_bytes = dip->logical_offset + dip->bytes -
			ordered_offset;
		ordered = NULL;
		goto again;
	}
out_done:
	bio->bi_private = dip->private;

	kfree(dip);

	/* If we had an error make sure to clear the uptodate flag */
	if (err)
		clear_bit(BIO_UPTODATE, &bio->bi_flags);
	dio_end_io(bio, err);
}