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
struct reiserfs_journal_list {int dummy; } ;
struct reiserfs_journal {int j_errno; } ;
struct reiserfs_jh {struct buffer_head* bh; int /*<<< orphan*/  list; } ;
struct list_head {int /*<<< orphan*/  prev; int /*<<< orphan*/  next; } ;
struct buffer_head {TYPE_1__* b_page; } ;
struct buffer_chunk {scalar_t__ nr; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 struct reiserfs_jh* JH_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  add_to_chunk (struct buffer_chunk*,struct buffer_head*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct buffer_chunk*)) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cond_resched_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_free_jh (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trylock_buffer (struct buffer_head*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  write_ordered_chunk (struct buffer_chunk*) ; 

__attribute__((used)) static int write_ordered_buffers(spinlock_t * lock,
				 struct reiserfs_journal *j,
				 struct reiserfs_journal_list *jl,
				 struct list_head *list)
{
	struct buffer_head *bh;
	struct reiserfs_jh *jh;
	int ret = j->j_errno;
	struct buffer_chunk chunk;
	struct list_head tmp;
	INIT_LIST_HEAD(&tmp);

	chunk.nr = 0;
	spin_lock(lock);
	while (!list_empty(list)) {
		jh = JH_ENTRY(list->next);
		bh = jh->bh;
		get_bh(bh);
		if (!trylock_buffer(bh)) {
			if (!buffer_dirty(bh)) {
				list_move(&jh->list, &tmp);
				goto loop_next;
			}
			spin_unlock(lock);
			if (chunk.nr)
				write_ordered_chunk(&chunk);
			wait_on_buffer(bh);
			cond_resched();
			spin_lock(lock);
			goto loop_next;
		}
		/* in theory, dirty non-uptodate buffers should never get here,
		 * but the upper layer io error paths still have a few quirks.
		 * Handle them here as gracefully as we can
		 */
		if (!buffer_uptodate(bh) && buffer_dirty(bh)) {
			clear_buffer_dirty(bh);
			ret = -EIO;
		}
		if (buffer_dirty(bh)) {
			list_move(&jh->list, &tmp);
			add_to_chunk(&chunk, bh, lock, write_ordered_chunk);
		} else {
			reiserfs_free_jh(bh);
			unlock_buffer(bh);
		}
	      loop_next:
		put_bh(bh);
		cond_resched_lock(lock);
	}
	if (chunk.nr) {
		spin_unlock(lock);
		write_ordered_chunk(&chunk);
		spin_lock(lock);
	}
	while (!list_empty(&tmp)) {
		jh = JH_ENTRY(tmp.prev);
		bh = jh->bh;
		get_bh(bh);
		reiserfs_free_jh(bh);

		if (buffer_locked(bh)) {
			spin_unlock(lock);
			wait_on_buffer(bh);
			spin_lock(lock);
		}
		if (!buffer_uptodate(bh)) {
			ret = -EIO;
		}
		/* ugly interaction with invalidatepage here.
		 * reiserfs_invalidate_page will pin any buffer that has a valid
		 * journal head from an older transaction.  If someone else sets
		 * our buffer dirty after we write it in the first loop, and
		 * then someone truncates the page away, nobody will ever write
		 * the buffer. We're safe if we write the page one last time
		 * after freeing the journal header.
		 */
		if (buffer_dirty(bh) && unlikely(bh->b_page->mapping == NULL)) {
			spin_unlock(lock);
			ll_rw_block(WRITE, 1, &bh);
			spin_lock(lock);
		}
		put_bh(bh);
		cond_resched_lock(lock);
	}
	spin_unlock(lock);
	return ret;
}