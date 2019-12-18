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
struct ubifs_inode {unsigned int ui_size; int /*<<< orphan*/  ui_mutex; } ;
struct ubifs_info {int /*<<< orphan*/  dirty_pg_cnt; } ;
struct page {int /*<<< orphan*/  index; } ;
struct inode {unsigned int i_size; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_page_dirty_nobuffers (struct page*) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_budget (struct ubifs_info*,struct page*,struct ubifs_inode*,int) ; 
 int /*<<< orphan*/  dbg_gen (char*,unsigned int,unsigned int,...) ; 
 unsigned int do_readpage (struct page*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ubifs_write_end(struct file *file, struct address_space *mapping,
			   loff_t pos, unsigned len, unsigned copied,
			   struct page *page, void *fsdata)
{
	struct inode *inode = mapping->host;
	struct ubifs_inode *ui = ubifs_inode(inode);
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	loff_t end_pos = pos + len;
	int appending = !!(end_pos > inode->i_size);

	dbg_gen("ino %lu, pos %llu, pg %lu, len %u, copied %d, i_size %lld",
		inode->i_ino, pos, page->index, len, copied, inode->i_size);

	if (unlikely(copied < len && len == PAGE_CACHE_SIZE)) {
		/*
		 * VFS copied less data to the page that it intended and
		 * declared in its '->write_begin()' call via the @len
		 * argument. If the page was not up-to-date, and @len was
		 * @PAGE_CACHE_SIZE, the 'ubifs_write_begin()' function did
		 * not load it from the media (for optimization reasons). This
		 * means that part of the page contains garbage. So read the
		 * page now.
		 */
		dbg_gen("copied %d instead of %d, read page and repeat",
			copied, len);
		cancel_budget(c, page, ui, appending);

		/*
		 * Return 0 to force VFS to repeat the whole operation, or the
		 * error code if 'do_readpage()' fails.
		 */
		copied = do_readpage(page);
		goto out;
	}

	if (!PagePrivate(page)) {
		SetPagePrivate(page);
		atomic_long_inc(&c->dirty_pg_cnt);
		__set_page_dirty_nobuffers(page);
	}

	if (appending) {
		i_size_write(inode, end_pos);
		ui->ui_size = end_pos;
		/*
		 * Note, we do not set @I_DIRTY_PAGES (which means that the
		 * inode has dirty pages), this has been done in
		 * '__set_page_dirty_nobuffers()'.
		 */
		__mark_inode_dirty(inode, I_DIRTY_DATASYNC);
		ubifs_assert(mutex_is_locked(&ui->ui_mutex));
		mutex_unlock(&ui->ui_mutex);
	}

out:
	unlock_page(page);
	page_cache_release(page);
	return copied;
}