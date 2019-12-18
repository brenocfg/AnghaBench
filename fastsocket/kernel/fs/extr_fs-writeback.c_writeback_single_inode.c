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
struct writeback_control {scalar_t__ sync_mode; scalar_t__ nr_to_write; } ;
struct inode {int i_state; int /*<<< orphan*/  i_list; int /*<<< orphan*/  i_count; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I_CLEAR ; 
 int I_DIRTY ; 
 unsigned int I_DIRTY_DATASYNC ; 
 int I_DIRTY_PAGES ; 
 unsigned int I_DIRTY_SYNC ; 
 int I_FREEING ; 
 int I_SYNC ; 
 int I_WILL_FREE ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WB_SYNC_ALL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int do_writepages (struct address_space*,struct writeback_control*) ; 
 int filemap_fdatawait (struct address_space*) ; 
 int /*<<< orphan*/  inode_in_use ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  inode_sync_complete (struct inode*) ; 
 int /*<<< orphan*/  inode_unused ; 
 int /*<<< orphan*/  inode_wait_for_writeback (struct inode*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirty_tail (struct inode*) ; 
 int /*<<< orphan*/  requeue_io (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int write_inode (struct inode*,struct writeback_control*) ; 

__attribute__((used)) static int
writeback_single_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct address_space *mapping = inode->i_mapping;
	unsigned dirty;
	int ret;

	if (!atomic_read(&inode->i_count))
		WARN_ON(!(inode->i_state & (I_WILL_FREE|I_FREEING)));
	else
		WARN_ON(inode->i_state & I_WILL_FREE);

	if (inode->i_state & I_SYNC) {
		/*
		 * If this inode is locked for writeback and we are not doing
		 * writeback-for-data-integrity, move it to b_more_io so that
		 * writeback can proceed with the other inodes on s_io.
		 *
		 * We'll have another go at writing back this inode when we
		 * completed a full scan of b_io.
		 */
		if (wbc->sync_mode != WB_SYNC_ALL) {
			requeue_io(inode);
			return 0;
		}

		/*
		 * It's a data-integrity sync.  We must wait.
		 */
		inode_wait_for_writeback(inode);
	}

	BUG_ON(inode->i_state & I_SYNC);

	/* Set I_SYNC, reset I_DIRTY */
	dirty = inode->i_state & I_DIRTY;
	inode->i_state |= I_SYNC;
	inode->i_state &= ~I_DIRTY;

	spin_unlock(&inode_lock);

	ret = do_writepages(mapping, wbc);

	/*
	 * Make sure to wait on the data before writing out the metadata.
	 * This is important for filesystems that modify metadata on data
	 * I/O completion.
	 */
	if (wbc->sync_mode == WB_SYNC_ALL) {
		int err = filemap_fdatawait(mapping);
		if (ret == 0)
			ret = err;
	}

	/* Don't write the inode if only I_DIRTY_PAGES was set */
	if (dirty & (I_DIRTY_SYNC | I_DIRTY_DATASYNC)) {
		int err = write_inode(inode, wbc);
		if (ret == 0)
			ret = err;
	}

	spin_lock(&inode_lock);
	inode->i_state &= ~I_SYNC;
	if (!(inode->i_state & (I_FREEING | I_CLEAR))) {
		if (mapping_tagged(mapping, PAGECACHE_TAG_DIRTY)) {
			/*
			 * We didn't write back all the pages.  nfs_writepages()
			 * sometimes bales out without doing anything.
			 */
			inode->i_state |= I_DIRTY_PAGES;
			if (wbc->nr_to_write <= 0) {
				/*
				 * slice used up: queue for next turn
				 */
				requeue_io(inode);
			} else {
				/*
				 * Writeback blocked by something other than
				 * congestion. Delay the inode for some time to
				 * avoid spinning on the CPU (100% iowait)
				 * retrying writeback of the dirty page/inode
				 * that cannot be performed immediately. 
				 */
				redirty_tail(inode);
			}
		} else if (inode->i_state & I_DIRTY) {
			/*
			 * Filesystems can dirty the inode during writeback
			 * operations, such as delayed allocation during
			 * submission or metadata updates after data IO
			 * completion.
			 */
			redirty_tail(inode);
		} else if (atomic_read(&inode->i_count)) {
			/*
			 * The inode is clean, inuse
			 */
			list_move(&inode->i_list, &inode_in_use);
		} else {
			/*
			 * The inode is clean, unused
			 */
			list_move(&inode->i_list, &inode_unused);
		}
	}
	inode_sync_complete(inode);
	return ret;
}