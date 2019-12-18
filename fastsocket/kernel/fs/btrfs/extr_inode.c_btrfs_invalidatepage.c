#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_ordered_extent {int dummy; } ;
struct TYPE_4__ {struct extent_io_tree io_tree; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int EXTENT_DELALLOC ; 
 int EXTENT_DIRTY ; 
 int EXTENT_DO_ACCOUNTING ; 
 int EXTENT_LOCKED ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 scalar_t__ PagePrivate (struct page*) ; 
 scalar_t__ TestClearPagePrivate2 (struct page*) ; 
 int /*<<< orphan*/  __btrfs_releasepage (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_dec_test_ordered_pending (struct inode*,struct btrfs_ordered_extent**,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_finish_ordered_io (struct btrfs_ordered_extent*) ; 
 struct btrfs_ordered_extent* btrfs_lookup_ordered_extent (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_releasepage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_extent_bit (struct extent_io_tree*,scalar_t__,scalar_t__,int,int,int,struct extent_state**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct extent_state**) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static void btrfs_invalidatepage(struct page *page, unsigned long offset)
{
	struct inode *inode = page->mapping->host;
	struct extent_io_tree *tree;
	struct btrfs_ordered_extent *ordered;
	struct extent_state *cached_state = NULL;
	u64 page_start = page_offset(page);
	u64 page_end = page_start + PAGE_CACHE_SIZE - 1;

	/*
	 * we have the page locked, so new writeback can't start,
	 * and the dirty bit won't be cleared while we are here.
	 *
	 * Wait for IO on this page so that we can safely clear
	 * the PagePrivate2 bit and do ordered accounting
	 */
	wait_on_page_writeback(page);

	tree = &BTRFS_I(inode)->io_tree;
	if (offset) {
		btrfs_releasepage(page, GFP_NOFS);
		return;
	}
	lock_extent_bits(tree, page_start, page_end, 0, &cached_state);
	ordered = btrfs_lookup_ordered_extent(inode,
					   page_offset(page));
	if (ordered) {
		/*
		 * IO on this page will never be started, so we need
		 * to account for any ordered extents now
		 */
		clear_extent_bit(tree, page_start, page_end,
				 EXTENT_DIRTY | EXTENT_DELALLOC |
				 EXTENT_LOCKED | EXTENT_DO_ACCOUNTING, 1, 0,
				 &cached_state, GFP_NOFS);
		/*
		 * whoever cleared the private bit is responsible
		 * for the finish_ordered_io
		 */
		if (TestClearPagePrivate2(page) &&
		    btrfs_dec_test_ordered_pending(inode, &ordered, page_start,
						   PAGE_CACHE_SIZE, 1)) {
			btrfs_finish_ordered_io(ordered);
		}
		btrfs_put_ordered_extent(ordered);
		cached_state = NULL;
		lock_extent_bits(tree, page_start, page_end, 0, &cached_state);
	}
	clear_extent_bit(tree, page_start, page_end,
		 EXTENT_LOCKED | EXTENT_DIRTY | EXTENT_DELALLOC |
		 EXTENT_DO_ACCOUNTING, 1, 1, &cached_state, GFP_NOFS);
	__btrfs_releasepage(page, GFP_NOFS);

	ClearPageChecked(page);
	if (PagePrivate(page)) {
		ClearPagePrivate(page);
		set_page_private(page, 0);
		page_cache_release(page);
	}
}