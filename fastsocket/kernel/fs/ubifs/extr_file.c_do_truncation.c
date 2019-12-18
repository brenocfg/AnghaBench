#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ubifs_inode {int ui_size; int /*<<< orphan*/  ui_mutex; } ;
struct ubifs_info {scalar_t__ nospace_rp; scalar_t__ nospace; } ;
struct ubifs_budget_req {int dirtied_page; int dirtied_ino; int /*<<< orphan*/  dirtied_ino_d; } ;
struct page {int dummy; } ;
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_ino; } ;
struct iattr {int ia_size; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 int ENOSPC ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 scalar_t__ UBIFS_BLOCKS_PER_PAGE_SHIFT ; 
 int UBIFS_BLOCK_SIZE ; 
 int /*<<< orphan*/  UBIFS_TRUN_NODE_SZ ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  do_attr_changes (struct inode*,struct iattr const*) ; 
 int do_writepage (struct page*,int) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ubifs_budget_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_current_time (struct inode*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_truncate (struct ubifs_info*,struct inode*,int,int) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int vmtruncate (struct inode*,int) ; 

__attribute__((used)) static int do_truncation(struct ubifs_info *c, struct inode *inode,
			 const struct iattr *attr)
{
	int err;
	struct ubifs_budget_req req;
	loff_t old_size = inode->i_size, new_size = attr->ia_size;
	int offset = new_size & (UBIFS_BLOCK_SIZE - 1), budgeted = 1;
	struct ubifs_inode *ui = ubifs_inode(inode);

	dbg_gen("ino %lu, size %lld -> %lld", inode->i_ino, old_size, new_size);
	memset(&req, 0, sizeof(struct ubifs_budget_req));

	/*
	 * If this is truncation to a smaller size, and we do not truncate on a
	 * block boundary, budget for changing one data block, because the last
	 * block will be re-written.
	 */
	if (new_size & (UBIFS_BLOCK_SIZE - 1))
		req.dirtied_page = 1;

	req.dirtied_ino = 1;
	/* A funny way to budget for truncation node */
	req.dirtied_ino_d = UBIFS_TRUN_NODE_SZ;
	err = ubifs_budget_space(c, &req);
	if (err) {
		/*
		 * Treat truncations to zero as deletion and always allow them,
		 * just like we do for '->unlink()'.
		 */
		if (new_size || err != -ENOSPC)
			return err;
		budgeted = 0;
	}

	err = vmtruncate(inode, new_size);
	if (err)
		goto out_budg;

	if (offset) {
		pgoff_t index = new_size >> PAGE_CACHE_SHIFT;
		struct page *page;

		page = find_lock_page(inode->i_mapping, index);
		if (page) {
			if (PageDirty(page)) {
				/*
				 * 'ubifs_jnl_truncate()' will try to truncate
				 * the last data node, but it contains
				 * out-of-date data because the page is dirty.
				 * Write the page now, so that
				 * 'ubifs_jnl_truncate()' will see an already
				 * truncated (and up to date) data node.
				 */
				ubifs_assert(PagePrivate(page));

				clear_page_dirty_for_io(page);
				if (UBIFS_BLOCKS_PER_PAGE_SHIFT)
					offset = new_size &
						 (PAGE_CACHE_SIZE - 1);
				err = do_writepage(page, offset);
				page_cache_release(page);
				if (err)
					goto out_budg;
				/*
				 * We could now tell 'ubifs_jnl_truncate()' not
				 * to read the last block.
				 */
			} else {
				/*
				 * We could 'kmap()' the page and pass the data
				 * to 'ubifs_jnl_truncate()' to save it from
				 * having to read it.
				 */
				unlock_page(page);
				page_cache_release(page);
			}
		}
	}

	mutex_lock(&ui->ui_mutex);
	ui->ui_size = inode->i_size;
	/* Truncation changes inode [mc]time */
	inode->i_mtime = inode->i_ctime = ubifs_current_time(inode);
	/* Other attributes may be changed at the same time as well */
	do_attr_changes(inode, attr);
	err = ubifs_jnl_truncate(c, inode, old_size, new_size);
	mutex_unlock(&ui->ui_mutex);

out_budg:
	if (budgeted)
		ubifs_release_budget(c, &req);
	else {
		c->nospace = c->nospace_rp = 0;
		smp_wmb();
	}
	return err;
}