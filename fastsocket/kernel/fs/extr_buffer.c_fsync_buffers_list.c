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
struct list_head {int /*<<< orphan*/  prev; int /*<<< orphan*/  next; } ;
struct buffer_head {struct address_space* b_assoc_map; int /*<<< orphan*/  b_assoc_buffers; } ;
struct address_space {struct list_head private_list; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 struct buffer_head* BH_ENTRY (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  WRITE_SYNC_PLUG ; 
 int /*<<< orphan*/  __remove_assoc_queue (struct buffer_head*) ; 
 int /*<<< orphan*/  blk_run_address_space (struct address_space*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int osync_buffers_list (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  write_dirty_buffer (struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsync_buffers_list(spinlock_t *lock, struct list_head *list)
{
	struct buffer_head *bh;
	struct list_head tmp;
	struct address_space *mapping, *prev_mapping = NULL;
	int err = 0, err2;

	INIT_LIST_HEAD(&tmp);

	spin_lock(lock);
	while (!list_empty(list)) {
		bh = BH_ENTRY(list->next);
		mapping = bh->b_assoc_map;
		__remove_assoc_queue(bh);
		/* Avoid race with mark_buffer_dirty_inode() which does
		 * a lockless check and we rely on seeing the dirty bit */
		smp_mb();
		if (buffer_dirty(bh) || buffer_locked(bh)) {
			list_add(&bh->b_assoc_buffers, &tmp);
			bh->b_assoc_map = mapping;
			if (buffer_dirty(bh)) {
				get_bh(bh);
				spin_unlock(lock);
				/*
				 * Ensure any pending I/O completes so that
				 * write_dirty_buffer() actually writes the
				 * current contents - it is a noop if I/O is
				 * still in flight on potentially older
				 * contents.
				 */
				write_dirty_buffer(bh, WRITE_SYNC_PLUG);

				/*
				 * Kick off IO for the previous mapping. Note
				 * that we will not run the very last mapping,
				 * wait_on_buffer() will do that for us
				 * through sync_buffer().
				 */
				if (prev_mapping && prev_mapping != mapping)
					blk_run_address_space(prev_mapping);
				prev_mapping = mapping;

				brelse(bh);
				spin_lock(lock);
			}
		}
	}

	while (!list_empty(&tmp)) {
		bh = BH_ENTRY(tmp.prev);
		get_bh(bh);
		mapping = bh->b_assoc_map;
		__remove_assoc_queue(bh);
		/* Avoid race with mark_buffer_dirty_inode() which does
		 * a lockless check and we rely on seeing the dirty bit */
		smp_mb();
		if (buffer_dirty(bh)) {
			list_add(&bh->b_assoc_buffers,
				 &mapping->private_list);
			bh->b_assoc_map = mapping;
		}
		spin_unlock(lock);
		wait_on_buffer(bh);
		if (!buffer_uptodate(bh))
			err = -EIO;
		brelse(bh);
		spin_lock(lock);
	}
	
	spin_unlock(lock);
	err2 = osync_buffers_list(lock, list);
	if (err)
		return err;
	else
		return err2;
}