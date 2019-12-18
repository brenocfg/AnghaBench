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
struct page {scalar_t__ index; TYPE_1__* mapping; } ;
struct ocfs2_inode_info {int ip_dyn_features; int /*<<< orphan*/  ip_alloc_sem; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int AOP_TRUNCATED_PAGE ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 scalar_t__ PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int block_read_full_page (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct file*,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_get_block ; 
 int ocfs2_inode_lock_with_page (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_readpage_inline (struct inode*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_user (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_readpage(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	loff_t start = (loff_t)page->index << PAGE_CACHE_SHIFT;
	int ret, unlock = 1;

	mlog_entry("(0x%p, %lu)\n", file, (page ? page->index : 0));

	ret = ocfs2_inode_lock_with_page(inode, NULL, 0, page);
	if (ret != 0) {
		if (ret == AOP_TRUNCATED_PAGE)
			unlock = 0;
		mlog_errno(ret);
		goto out;
	}

	if (down_read_trylock(&oi->ip_alloc_sem) == 0) {
		ret = AOP_TRUNCATED_PAGE;
		goto out_inode_unlock;
	}

	/*
	 * i_size might have just been updated as we grabed the meta lock.  We
	 * might now be discovering a truncate that hit on another node.
	 * block_read_full_page->get_block freaks out if it is asked to read
	 * beyond the end of a file, so we check here.  Callers
	 * (generic_file_read, vm_ops->fault) are clever enough to check i_size
	 * and notice that the page they just read isn't needed.
	 *
	 * XXX sys_readahead() seems to get that wrong?
	 */
	if (start >= i_size_read(inode)) {
		zero_user(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
		ret = 0;
		goto out_alloc;
	}

	if (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		ret = ocfs2_readpage_inline(inode, page);
	else
		ret = block_read_full_page(page, ocfs2_get_block);
	unlock = 0;

out_alloc:
	up_read(&OCFS2_I(inode)->ip_alloc_sem);
out_inode_unlock:
	ocfs2_inode_unlock(inode, 0);
out:
	if (unlock)
		unlock_page(page);
	mlog_exit(ret);
	return ret;
}