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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct page {struct address_space* mapping; } ;
struct inode {int dummy; } ;
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_root {int sectorsize; } ;
struct btrfs_ordered_extent {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct extent_io_tree io_tree; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int EIO ; 
 int ENOMEM ; 
 int EXTENT_DELALLOC ; 
 int EXTENT_DIRTY ; 
 int EXTENT_DO_ACCOUNTING ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  btrfs_alloc_write_mask (struct address_space*) ; 
 int /*<<< orphan*/  btrfs_delalloc_release_space (struct inode*,int) ; 
 int btrfs_delalloc_reserve_space (struct inode*,int) ; 
 struct btrfs_ordered_extent* btrfs_lookup_ordered_extent (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int btrfs_readpage (int /*<<< orphan*/ *,struct page*) ; 
 int btrfs_set_extent_delalloc (struct inode*,scalar_t__,scalar_t__,struct extent_state**) ; 
 int /*<<< orphan*/  btrfs_start_ordered_extent (struct inode*,struct btrfs_ordered_extent*,int) ; 
 int /*<<< orphan*/  clear_extent_bit (struct extent_io_tree*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct extent_state**,int /*<<< orphan*/ ) ; 
 struct page* find_or_create_page (struct address_space*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct extent_state**) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_page_extent_mapped (struct page*) ; 
 int /*<<< orphan*/  unlock_extent_cached (struct extent_io_tree*,scalar_t__,scalar_t__,struct extent_state**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static int btrfs_truncate_page(struct address_space *mapping, loff_t from)
{
	struct inode *inode = mapping->host;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct btrfs_ordered_extent *ordered;
	struct extent_state *cached_state = NULL;
	char *kaddr;
	u32 blocksize = root->sectorsize;
	pgoff_t index = from >> PAGE_CACHE_SHIFT;
	unsigned offset = from & (PAGE_CACHE_SIZE-1);
	struct page *page;
	gfp_t mask = btrfs_alloc_write_mask(mapping);
	int ret = 0;
	u64 page_start;
	u64 page_end;

	if ((offset & (blocksize - 1)) == 0)
		goto out;
	ret = btrfs_delalloc_reserve_space(inode, PAGE_CACHE_SIZE);
	if (ret)
		goto out;

	ret = -ENOMEM;
again:
	page = find_or_create_page(mapping, index, mask);
	if (!page) {
		btrfs_delalloc_release_space(inode, PAGE_CACHE_SIZE);
		goto out;
	}

	page_start = page_offset(page);
	page_end = page_start + PAGE_CACHE_SIZE - 1;

	if (!PageUptodate(page)) {
		ret = btrfs_readpage(NULL, page);
		lock_page(page);
		if (page->mapping != mapping) {
			unlock_page(page);
			page_cache_release(page);
			goto again;
		}
		if (!PageUptodate(page)) {
			ret = -EIO;
			goto out_unlock;
		}
	}
	wait_on_page_writeback(page);

	lock_extent_bits(io_tree, page_start, page_end, 0, &cached_state);
	set_page_extent_mapped(page);

	ordered = btrfs_lookup_ordered_extent(inode, page_start);
	if (ordered) {
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state, GFP_NOFS);
		unlock_page(page);
		page_cache_release(page);
		btrfs_start_ordered_extent(inode, ordered, 1);
		btrfs_put_ordered_extent(ordered);
		goto again;
	}

	clear_extent_bit(&BTRFS_I(inode)->io_tree, page_start, page_end,
			  EXTENT_DIRTY | EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING,
			  0, 0, &cached_state, GFP_NOFS);

	ret = btrfs_set_extent_delalloc(inode, page_start, page_end,
					&cached_state);
	if (ret) {
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state, GFP_NOFS);
		goto out_unlock;
	}

	ret = 0;
	if (offset != PAGE_CACHE_SIZE) {
		kaddr = kmap(page);
		memset(kaddr + offset, 0, PAGE_CACHE_SIZE - offset);
		flush_dcache_page(page);
		kunmap(page);
	}
	ClearPageChecked(page);
	set_page_dirty(page);
	unlock_extent_cached(io_tree, page_start, page_end, &cached_state,
			     GFP_NOFS);

out_unlock:
	if (ret)
		btrfs_delalloc_release_space(inode, PAGE_CACHE_SIZE);
	unlock_page(page);
	page_cache_release(page);
out:
	return ret;
}