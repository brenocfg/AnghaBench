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
struct vm_fault {struct page* page; } ;
struct vm_area_struct {TYPE_4__* vm_file; } ;
struct page {scalar_t__ mapping; int index; } ;
struct inode {scalar_t__ i_mapping; TYPE_3__* i_sb; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  get_block_t ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct TYPE_8__ {TYPE_2__ f_path; } ;
struct TYPE_7__ {scalar_t__ s_frozen; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int PAGE_CACHE_MASK ; 
 int PAGE_CACHE_SHIFT ; 
 unsigned long PAGE_CACHE_SIZE ; 
 scalar_t__ SB_UNFROZEN ; 
 int block_commit_write (struct page*,int /*<<< orphan*/ ,unsigned long) ; 
 int block_prepare_write (struct page*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_update_time (TYPE_4__*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  sb_has_new_freeze (TYPE_3__*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

int __block_page_mkwrite(struct vm_area_struct *vma, struct vm_fault *vmf,
			 get_block_t get_block)
{
	struct page *page = vmf->page;
	struct inode *inode = vma->vm_file->f_path.dentry->d_inode;
	unsigned long end;
	loff_t size;
	int ret;

	/*
	 * Update file times before taking page lock. We may end up failing the
	 * fault so this update may be superfluous but who really cares...
	 */
	file_update_time(vma->vm_file);

	lock_page(page);
	size = i_size_read(inode);
	if ((page->mapping != inode->i_mapping) ||
	    (page_offset(page) > size)) {
		/* We overload EFAULT to mean page got truncated */
		ret = -EFAULT;
		goto out_unlock;
	}

	/* page is wholly or partially inside EOF */
	if (((page->index + 1) << PAGE_CACHE_SHIFT) > size)
		end = size & ~PAGE_CACHE_MASK;
	else
		end = PAGE_CACHE_SIZE;

	ret = block_prepare_write(page, 0, end, get_block);
	if (!ret)
		ret = block_commit_write(page, 0, end);

	if (unlikely(ret < 0))
		goto out_unlock;
	/*
	 * OLD FREEZE PATH:
	 * Freezing in progress? We check after the page is marked dirty and
	 * with page lock held so if the test here fails, we are sure freezing
	 * code will wait during syncing until the page fault is done - at that
	 * point page will be dirty and unlocked so freezing code will write it
	 * and writeprotect it again.
	 */
	set_page_dirty(page);
	if (!sb_has_new_freeze(inode->i_sb) && inode->i_sb->s_frozen != SB_UNFROZEN) {
		ret = -EAGAIN;
		goto out_unlock;
	}
	wait_for_stable_page(page);
	return 0;
out_unlock:
	unlock_page(page);
	return ret;
}