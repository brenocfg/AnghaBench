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
struct writeback_control {int dummy; } ;
struct ubifs_inode {int synced_i_size; int /*<<< orphan*/  ui_lock; } ;
struct page {scalar_t__ index; int /*<<< orphan*/  flags; TYPE_1__* mapping; } ;
struct inode {TYPE_3__* i_sb; int /*<<< orphan*/  i_ino; } ;
typedef  scalar_t__ pgoff_t ;
typedef  int loff_t ;
struct TYPE_6__ {TYPE_2__* s_op; } ;
struct TYPE_5__ {int (* write_inode ) (struct inode*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int do_writepage (struct page*,int) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int i_size_read (struct inode*) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct inode*,int /*<<< orphan*/ *) ; 
 int stub2 (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ubifs_writepage(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct ubifs_inode *ui = ubifs_inode(inode);
	loff_t i_size =  i_size_read(inode), synced_i_size;
	pgoff_t end_index = i_size >> PAGE_CACHE_SHIFT;
	int err, len = i_size & (PAGE_CACHE_SIZE - 1);
	void *kaddr;

	dbg_gen("ino %lu, pg %lu, pg flags %#lx",
		inode->i_ino, page->index, page->flags);
	ubifs_assert(PagePrivate(page));

	/* Is the page fully outside @i_size? (truncate in progress) */
	if (page->index > end_index || (page->index == end_index && !len)) {
		err = 0;
		goto out_unlock;
	}

	spin_lock(&ui->ui_lock);
	synced_i_size = ui->synced_i_size;
	spin_unlock(&ui->ui_lock);

	/* Is the page fully inside @i_size? */
	if (page->index < end_index) {
		if (page->index >= synced_i_size >> PAGE_CACHE_SHIFT) {
			err = inode->i_sb->s_op->write_inode(inode, NULL);
			if (err)
				goto out_unlock;
			/*
			 * The inode has been written, but the write-buffer has
			 * not been synchronized, so in case of an unclean
			 * reboot we may end up with some pages beyond inode
			 * size, but they would be in the journal (because
			 * commit flushes write buffers) and recovery would deal
			 * with this.
			 */
		}
		return do_writepage(page, PAGE_CACHE_SIZE);
	}

	/*
	 * The page straddles @i_size. It must be zeroed out on each and every
	 * writepage invocation because it may be mmapped. "A file is mapped
	 * in multiples of the page size. For a file that is not a multiple of
	 * the page size, the remaining memory is zeroed when mapped, and
	 * writes to that region are not written out to the file."
	 */
	kaddr = kmap_atomic(page, KM_USER0);
	memset(kaddr + len, 0, PAGE_CACHE_SIZE - len);
	flush_dcache_page(page);
	kunmap_atomic(kaddr, KM_USER0);

	if (i_size > synced_i_size) {
		err = inode->i_sb->s_op->write_inode(inode, NULL);
		if (err)
			goto out_unlock;
	}

	return do_writepage(page, len);

out_unlock:
	unlock_page(page);
	return err;
}