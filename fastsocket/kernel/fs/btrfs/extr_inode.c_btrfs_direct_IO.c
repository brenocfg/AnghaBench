#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int dummy; } ;
struct file {TYPE_3__* f_mapping; } ;
struct extent_state {int dummy; } ;
struct btrfs_ordered_extent {int dummy; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;
struct TYPE_11__ {int /*<<< orphan*/  io_tree; TYPE_5__* root; } ;
struct TYPE_10__ {TYPE_2__* fs_info; } ;
struct TYPE_9__ {struct inode* host; } ;
struct TYPE_8__ {TYPE_1__* fs_devices; } ;
struct TYPE_7__ {int /*<<< orphan*/  latest_bdev; } ;

/* Variables and functions */
 TYPE_6__* BTRFS_I (struct inode*) ; 
 size_t EBUSY ; 
 size_t EIOCBQUEUED ; 
 int EXTENT_DELALLOC ; 
 int EXTENT_DO_ACCOUNTING ; 
 int EXTENT_LOCKED ; 
 int /*<<< orphan*/  EXTENT_UPTODATE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 size_t PAGE_CACHE_SHIFT ; 
 int WRITE ; 
 size_t __blockdev_direct_IO (int,struct kiocb*,struct inode*,int /*<<< orphan*/ ,struct iovec const*,size_t,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t btrfs_delalloc_reserve_space (struct inode*,size_t) ; 
 int /*<<< orphan*/  btrfs_get_blocks_direct ; 
 struct btrfs_ordered_extent* btrfs_lookup_ordered_range (struct inode*,size_t,size_t) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_start_ordered_extent (struct inode*,struct btrfs_ordered_extent*,int) ; 
 int /*<<< orphan*/  btrfs_submit_direct ; 
 scalar_t__ check_direct_IO (TYPE_5__*,int,struct kiocb*,struct iovec const*,size_t,unsigned long) ; 
 int /*<<< orphan*/  clear_extent_bit (int /*<<< orphan*/ *,size_t,size_t,int,int,int /*<<< orphan*/ ,struct extent_state**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 size_t filemap_write_and_wait_range (TYPE_3__*,size_t,size_t) ; 
 int /*<<< orphan*/  free_extent_state (struct extent_state*) ; 
 size_t invalidate_inode_pages2_range (TYPE_3__*,size_t,size_t) ; 
 size_t iov_length (struct iovec const*,unsigned long) ; 
 int /*<<< orphan*/  lock_extent_bits (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ,struct extent_state**) ; 
 size_t set_extent_bit (int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ *,struct extent_state**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_range_bit (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct extent_state*) ; 
 int /*<<< orphan*/  unlock_extent_cached (int /*<<< orphan*/ *,size_t,size_t,struct extent_state**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t btrfs_direct_IO(int rw, struct kiocb *iocb,
			const struct iovec *iov, loff_t offset,
			unsigned long nr_segs)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	struct btrfs_ordered_extent *ordered;
	struct extent_state *cached_state = NULL;
	u64 lockstart, lockend;
	ssize_t ret;
	int writing = rw & WRITE;
	int write_bits = 0;
	size_t count = iov_length(iov, nr_segs);

	if (check_direct_IO(BTRFS_I(inode)->root, rw, iocb, iov,
			    offset, nr_segs)) {
		return 0;
	}

	lockstart = offset;
	lockend = offset + count - 1;

	if (writing) {
		ret = btrfs_delalloc_reserve_space(inode, count);
		if (ret)
			goto out;
	}

	while (1) {
		lock_extent_bits(&BTRFS_I(inode)->io_tree, lockstart, lockend,
				 0, &cached_state);
		/*
		 * We're concerned with the entire range that we're going to be
		 * doing DIO to, so we need to make sure theres no ordered
		 * extents in this range.
		 */
		ordered = btrfs_lookup_ordered_range(inode, lockstart,
						     lockend - lockstart + 1);

		/*
		 * We need to make sure there are no buffered pages in this
		 * range either, we could have raced between the invalidate in
		 * generic_file_direct_write and locking the extent.  The
		 * invalidate needs to happen so that reads after a write do not
		 * get stale data.
		 */
		if (!ordered && (!writing ||
		    !test_range_bit(&BTRFS_I(inode)->io_tree,
				    lockstart, lockend, EXTENT_UPTODATE, 0,
				    cached_state)))
			break;

		unlock_extent_cached(&BTRFS_I(inode)->io_tree, lockstart, lockend,
				     &cached_state, GFP_NOFS);

		if (ordered) {
			btrfs_start_ordered_extent(inode, ordered, 1);
			btrfs_put_ordered_extent(ordered);
		} else {
			/* Screw you mmap */
			ret = filemap_write_and_wait_range(file->f_mapping,
							   lockstart,
							   lockend);
			if (ret)
				goto out;

			/*
			 * If we found a page that couldn't be invalidated just
			 * fall back to buffered.
			 */
			ret = invalidate_inode_pages2_range(file->f_mapping,
					lockstart >> PAGE_CACHE_SHIFT,
					lockend >> PAGE_CACHE_SHIFT);
			if (ret) {
				if (ret == -EBUSY)
					ret = 0;
				goto out;
			}
		}

		cond_resched();
	}

	/*
	 * we don't use btrfs_set_extent_delalloc because we don't want
	 * the dirty or uptodate bits
	 */
	if (writing) {
		write_bits = EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING;
		ret = set_extent_bit(&BTRFS_I(inode)->io_tree, lockstart, lockend,
				     EXTENT_DELALLOC, NULL, &cached_state,
				     GFP_NOFS);
		if (ret) {
			clear_extent_bit(&BTRFS_I(inode)->io_tree, lockstart,
					 lockend, EXTENT_LOCKED | write_bits,
					 1, 0, &cached_state, GFP_NOFS);
			goto out;
		}
	}

	free_extent_state(cached_state);
	cached_state = NULL;

	ret = __blockdev_direct_IO(rw, iocb, inode,
		   BTRFS_I(inode)->root->fs_info->fs_devices->latest_bdev,
		   iov, offset, nr_segs, btrfs_get_blocks_direct, NULL,
		   btrfs_submit_direct, 0);

	if (ret < 0 && ret != -EIOCBQUEUED) {
		clear_extent_bit(&BTRFS_I(inode)->io_tree, offset,
			      offset + iov_length(iov, nr_segs) - 1,
			      EXTENT_LOCKED | write_bits, 1, 0,
			      &cached_state, GFP_NOFS);
	} else if (ret >= 0 && ret < iov_length(iov, nr_segs)) {
		/*
		 * We're falling back to buffered, unlock the section we didn't
		 * do IO on.
		 */
		clear_extent_bit(&BTRFS_I(inode)->io_tree, offset + ret,
			      offset + iov_length(iov, nr_segs) - 1,
			      EXTENT_LOCKED | write_bits, 1, 0,
			      &cached_state, GFP_NOFS);
	}
out:
	free_extent_state(cached_state);
	return ret;
}