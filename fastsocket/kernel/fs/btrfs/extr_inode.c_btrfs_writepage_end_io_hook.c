#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct extent_state {int dummy; } ;
struct btrfs_workers {int dummy; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct TYPE_7__ {scalar_t__ flags; int /*<<< orphan*/  func; } ;
struct btrfs_ordered_extent {TYPE_3__ work; } ;
struct TYPE_8__ {struct btrfs_root* root; } ;
struct TYPE_6__ {struct btrfs_workers endio_write_workers; struct btrfs_workers endio_freespace_worker; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  ClearPagePrivate2 (struct page*) ; 
 int /*<<< orphan*/  btrfs_dec_test_ordered_pending (struct inode*,struct btrfs_ordered_extent**,scalar_t__,scalar_t__,int) ; 
 scalar_t__ btrfs_is_free_space_inode (struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_queue_worker (struct btrfs_workers*,TYPE_3__*) ; 
 int /*<<< orphan*/  finish_ordered_fn ; 
 int /*<<< orphan*/  trace_btrfs_writepage_end_io_hook (struct page*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int btrfs_writepage_end_io_hook(struct page *page, u64 start, u64 end,
				struct extent_state *state, int uptodate)
{
	struct inode *inode = page->mapping->host;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_ordered_extent *ordered_extent = NULL;
	struct btrfs_workers *workers;

	trace_btrfs_writepage_end_io_hook(page, start, end, uptodate);

	ClearPagePrivate2(page);
	if (!btrfs_dec_test_ordered_pending(inode, &ordered_extent, start,
					    end - start + 1, uptodate))
		return 0;

	ordered_extent->work.func = finish_ordered_fn;
	ordered_extent->work.flags = 0;

	if (btrfs_is_free_space_inode(root, inode))
		workers = &root->fs_info->endio_freespace_worker;
	else
		workers = &root->fs_info->endio_write_workers;
	btrfs_queue_worker(workers, &ordered_extent->work);

	return 0;
}