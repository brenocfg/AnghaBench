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
typedef  unsigned long u64 ;
struct vm_fault {struct page* page; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_file; } ;
struct page {scalar_t__ mapping; } ;
struct inode {scalar_t__ i_mapping; int /*<<< orphan*/  i_sb; } ;
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  log_transid; TYPE_1__* fs_info; } ;
struct btrfs_ordered_extent {int dummy; } ;
typedef  unsigned long loff_t ;
struct TYPE_6__ {struct btrfs_root* root; int /*<<< orphan*/  last_sub_trans; int /*<<< orphan*/  last_trans; struct extent_io_tree io_tree; } ;
struct TYPE_5__ {struct inode* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  generation; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int ENOMEM ; 
 int EXTENT_DELALLOC ; 
 int EXTENT_DIRTY ; 
 int EXTENT_DO_ACCOUNTING ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned long PAGE_CACHE_MASK ; 
 unsigned long PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int VM_FAULT_LOCKED ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  btrfs_delalloc_release_space (struct inode*,unsigned long) ; 
 int btrfs_delalloc_reserve_space (struct inode*,unsigned long) ; 
 struct btrfs_ordered_extent* btrfs_lookup_ordered_extent (struct inode*,unsigned long) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int btrfs_set_extent_delalloc (struct inode*,unsigned long,unsigned long,struct extent_state**) ; 
 int /*<<< orphan*/  btrfs_start_ordered_extent (struct inode*,struct btrfs_ordered_extent*,int) ; 
 int btrfs_update_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_extent_bit (struct extent_io_tree*,unsigned long,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct extent_state**,int /*<<< orphan*/ ) ; 
 TYPE_2__* fdentry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 unsigned long i_size_read (struct inode*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,unsigned long,unsigned long,int /*<<< orphan*/ ,struct extent_state**) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long page_offset (struct page*) ; 
 int /*<<< orphan*/  sb_end_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_page_extent_mapped (struct page*) ; 
 int /*<<< orphan*/  unlock_extent_cached (struct extent_io_tree*,unsigned long,unsigned long,struct extent_state**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int btrfs_page_mkwrite(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct page *page = vmf->page;
	struct inode *inode = fdentry(vma->vm_file)->d_inode;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct btrfs_ordered_extent *ordered;
	struct extent_state *cached_state = NULL;
	char *kaddr;
	unsigned long zero_start;
	loff_t size;
	int ret;
	int reserved = 0;
	u64 page_start;
	u64 page_end;

	sb_start_pagefault(inode->i_sb);
	ret  = btrfs_delalloc_reserve_space(inode, PAGE_CACHE_SIZE);
	if (!ret) {
		ret = btrfs_update_time(vma->vm_file);
		reserved = 1;
	}
	if (ret) {
		if (ret == -ENOMEM)
			ret = VM_FAULT_OOM;
		else /* -ENOSPC, -EIO, etc */
			ret = VM_FAULT_SIGBUS;
		if (reserved)
			goto out;
		goto out_noreserve;
	}

	ret = VM_FAULT_NOPAGE; /* make the VM retry the fault */
again:
	lock_page(page);
	size = i_size_read(inode);
	page_start = page_offset(page);
	page_end = page_start + PAGE_CACHE_SIZE - 1;

	if ((page->mapping != inode->i_mapping) ||
	    (page_start >= size)) {
		/* page got truncated out from underneath us */
		goto out_unlock;
	}
	wait_on_page_writeback(page);

	lock_extent_bits(io_tree, page_start, page_end, 0, &cached_state);
	set_page_extent_mapped(page);

	/*
	 * we can't set the delalloc bits if there are pending ordered
	 * extents.  Drop our locks and wait for them to finish
	 */
	ordered = btrfs_lookup_ordered_extent(inode, page_start);
	if (ordered) {
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state, GFP_NOFS);
		unlock_page(page);
		btrfs_start_ordered_extent(inode, ordered, 1);
		btrfs_put_ordered_extent(ordered);
		goto again;
	}

	/*
	 * XXX - page_mkwrite gets called every time the page is dirtied, even
	 * if it was already dirty, so for space accounting reasons we need to
	 * clear any delalloc bits for the range we are fixing to save.  There
	 * is probably a better way to do this, but for now keep consistent with
	 * prepare_pages in the normal write path.
	 */
	clear_extent_bit(&BTRFS_I(inode)->io_tree, page_start, page_end,
			  EXTENT_DIRTY | EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING,
			  0, 0, &cached_state, GFP_NOFS);

	ret = btrfs_set_extent_delalloc(inode, page_start, page_end,
					&cached_state);
	if (ret) {
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state, GFP_NOFS);
		ret = VM_FAULT_SIGBUS;
		goto out_unlock;
	}
	ret = 0;

	/* page is wholly or partially inside EOF */
	if (page_start + PAGE_CACHE_SIZE > size)
		zero_start = size & ~PAGE_CACHE_MASK;
	else
		zero_start = PAGE_CACHE_SIZE;

	if (zero_start != PAGE_CACHE_SIZE) {
		kaddr = kmap(page);
		memset(kaddr + zero_start, 0, PAGE_CACHE_SIZE - zero_start);
		flush_dcache_page(page);
		kunmap(page);
	}
	ClearPageChecked(page);
	set_page_dirty(page);
	SetPageUptodate(page);

	BTRFS_I(inode)->last_trans = root->fs_info->generation;
	BTRFS_I(inode)->last_sub_trans = BTRFS_I(inode)->root->log_transid;

	unlock_extent_cached(io_tree, page_start, page_end, &cached_state, GFP_NOFS);

out_unlock:
	if (!ret) {
		sb_end_pagefault(inode->i_sb);
		return VM_FAULT_LOCKED;
	}
	unlock_page(page);
out:
	btrfs_delalloc_release_space(inode, PAGE_CACHE_SIZE);
out_noreserve:
	sb_end_pagefault(inode->i_sb);
	return ret;
}