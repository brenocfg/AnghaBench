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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_ordered_extent {int /*<<< orphan*/  disk_len; int /*<<< orphan*/  start; int /*<<< orphan*/  flags; } ;
struct btrfs_dio_private {int disk_bytenr; int /*<<< orphan*/  pending_bios; struct bio* orig_bio; scalar_t__ errors; scalar_t__ bytes; int /*<<< orphan*/  logical_offset; struct inode* inode; struct btrfs_dio_private* private; int /*<<< orphan*/ * csums; } ;
struct bio_vec {scalar_t__ bv_len; } ;
struct bio {int bi_vcnt; int /*<<< orphan*/  bi_end_io; struct btrfs_dio_private* bi_private; scalar_t__ bi_sector; struct bio_vec* bi_io_vec; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int flags; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATASUM ; 
 int /*<<< orphan*/  BTRFS_ORDERED_NOCOW ; 
 int /*<<< orphan*/  BTRFS_ORDERED_PREALLOC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int REQ_WRITE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int) ; 
 int /*<<< orphan*/  btrfs_endio_direct_read ; 
 int /*<<< orphan*/  btrfs_endio_direct_write ; 
 int /*<<< orphan*/  btrfs_free_reserved_extent (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_ordered_extent* btrfs_lookup_ordered_extent (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int btrfs_submit_direct_hook (int,struct btrfs_dio_private*,int) ; 
 int /*<<< orphan*/  kfree (struct btrfs_dio_private*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_submit_direct(int rw, struct bio *bio, struct inode *inode,
				loff_t file_offset)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_dio_private *dip;
	struct bio_vec *bvec = bio->bi_io_vec;
	int skip_sum;
	int write = rw & REQ_WRITE;
	int ret = 0;

	skip_sum = BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM;

	dip = kmalloc(sizeof(*dip), GFP_NOFS);
	if (!dip) {
		ret = -ENOMEM;
		goto free_ordered;
	}
	dip->csums = NULL;

	/* Write's use the ordered csum stuff, so we don't need dip->csums */
	if (!write && !skip_sum) {
		dip->csums = kmalloc(sizeof(u32) * bio->bi_vcnt, GFP_NOFS);
		if (!dip->csums) {
			kfree(dip);
			ret = -ENOMEM;
			goto free_ordered;
		}
	}

	dip->private = bio->bi_private;
	dip->inode = inode;
	dip->logical_offset = file_offset;

	dip->bytes = 0;
	do {
		dip->bytes += bvec->bv_len;
		bvec++;
	} while (bvec <= (bio->bi_io_vec + bio->bi_vcnt - 1));

	dip->disk_bytenr = (u64)bio->bi_sector << 9;
	bio->bi_private = dip;
	dip->errors = 0;
	dip->orig_bio = bio;
	atomic_set(&dip->pending_bios, 0);

	if (write)
		bio->bi_end_io = btrfs_endio_direct_write;
	else
		bio->bi_end_io = btrfs_endio_direct_read;

	ret = btrfs_submit_direct_hook(rw, dip, skip_sum);
	if (!ret)
		return;
free_ordered:
	/*
	 * If this is a write, we need to clean up the reserved space and kill
	 * the ordered extent.
	 */
	if (write) {
		struct btrfs_ordered_extent *ordered;
		ordered = btrfs_lookup_ordered_extent(inode, file_offset);
		if (!test_bit(BTRFS_ORDERED_PREALLOC, &ordered->flags) &&
		    !test_bit(BTRFS_ORDERED_NOCOW, &ordered->flags))
			btrfs_free_reserved_extent(root, ordered->start,
						   ordered->disk_len);
		btrfs_put_ordered_extent(ordered);
		btrfs_put_ordered_extent(ordered);
	}
	bio_endio(bio, ret);
}