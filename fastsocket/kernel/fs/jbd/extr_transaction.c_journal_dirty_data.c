#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct journal_head {scalar_t__ b_jlist; TYPE_5__* b_transaction; } ;
struct buffer_head {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  j_list_lock; TYPE_5__* j_committing_transaction; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_7__ {TYPE_5__* h_transaction; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  t_tid; TYPE_1__* t_journal; } ;

/* Variables and functions */
 scalar_t__ BJ_Locked ; 
 scalar_t__ BJ_None ; 
 scalar_t__ BJ_Shadow ; 
 scalar_t__ BJ_SyncData ; 
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EIO ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  __journal_file_buffer (struct journal_head*,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  __journal_temp_unlink_buffer (struct journal_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 scalar_t__ is_handle_aborted (TYPE_2__*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,struct journal_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 struct journal_head* journal_add_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  journal_put_journal_head (struct journal_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 

int journal_dirty_data(handle_t *handle, struct buffer_head *bh)
{
	journal_t *journal = handle->h_transaction->t_journal;
	int need_brelse = 0;
	struct journal_head *jh;
	int ret = 0;

	if (is_handle_aborted(handle))
		return ret;

	jh = journal_add_journal_head(bh);
	JBUFFER_TRACE(jh, "entry");

	/*
	 * The buffer could *already* be dirty.  Writeout can start
	 * at any time.
	 */
	jbd_debug(4, "jh: %p, tid:%d\n", jh, handle->h_transaction->t_tid);

	/*
	 * What if the buffer is already part of a running transaction?
	 *
	 * There are two cases:
	 * 1) It is part of the current running transaction.  Refile it,
	 *    just in case we have allocated it as metadata, deallocated
	 *    it, then reallocated it as data.
	 * 2) It is part of the previous, still-committing transaction.
	 *    If all we want to do is to guarantee that the buffer will be
	 *    written to disk before this new transaction commits, then
	 *    being sure that the *previous* transaction has this same
	 *    property is sufficient for us!  Just leave it on its old
	 *    transaction.
	 *
	 * In case (2), the buffer must not already exist as metadata
	 * --- that would violate write ordering (a transaction is free
	 * to write its data at any point, even before the previous
	 * committing transaction has committed).  The caller must
	 * never, ever allow this to happen: there's nothing we can do
	 * about it in this layer.
	 */
	jbd_lock_bh_state(bh);
	spin_lock(&journal->j_list_lock);

	/* Now that we have bh_state locked, are we really still mapped? */
	if (!buffer_mapped(bh)) {
		JBUFFER_TRACE(jh, "unmapped buffer, bailing out");
		goto no_journal;
	}

	if (jh->b_transaction) {
		JBUFFER_TRACE(jh, "has transaction");
		if (jh->b_transaction != handle->h_transaction) {
			JBUFFER_TRACE(jh, "belongs to older transaction");
			J_ASSERT_JH(jh, jh->b_transaction ==
					journal->j_committing_transaction);

			/* @@@ IS THIS TRUE  ? */
			/*
			 * Not any more.  Scenario: someone does a write()
			 * in data=journal mode.  The buffer's transaction has
			 * moved into commit.  Then someone does another
			 * write() to the file.  We do the frozen data copyout
			 * and set b_next_transaction to point to j_running_t.
			 * And while we're in that state, someone does a
			 * writepage() in an attempt to pageout the same area
			 * of the file via a shared mapping.  At present that
			 * calls journal_dirty_data(), and we get right here.
			 * It may be too late to journal the data.  Simply
			 * falling through to the next test will suffice: the
			 * data will be dirty and wil be checkpointed.  The
			 * ordering comments in the next comment block still
			 * apply.
			 */
			//J_ASSERT_JH(jh, jh->b_next_transaction == NULL);

			/*
			 * If we're journalling data, and this buffer was
			 * subject to a write(), it could be metadata, forget
			 * or shadow against the committing transaction.  Now,
			 * someone has dirtied the same darn page via a mapping
			 * and it is being writepage()'d.
			 * We *could* just steal the page from commit, with some
			 * fancy locking there.  Instead, we just skip it -
			 * don't tie the page's buffers to the new transaction
			 * at all.
			 * Implication: if we crash before the writepage() data
			 * is written into the filesystem, recovery will replay
			 * the write() data.
			 */
			if (jh->b_jlist != BJ_None &&
					jh->b_jlist != BJ_SyncData &&
					jh->b_jlist != BJ_Locked) {
				JBUFFER_TRACE(jh, "Not stealing");
				goto no_journal;
			}

			/*
			 * This buffer may be undergoing writeout in commit.  We
			 * can't return from here and let the caller dirty it
			 * again because that can cause the write-out loop in
			 * commit to never terminate.
			 */
			if (buffer_dirty(bh)) {
				get_bh(bh);
				spin_unlock(&journal->j_list_lock);
				jbd_unlock_bh_state(bh);
				need_brelse = 1;
				sync_dirty_buffer(bh);
				jbd_lock_bh_state(bh);
				spin_lock(&journal->j_list_lock);
				/* Since we dropped the lock... */
				if (!buffer_mapped(bh)) {
					JBUFFER_TRACE(jh, "buffer got unmapped");
					goto no_journal;
				}
				/* The buffer may become locked again at any
				   time if it is redirtied */
			}

			/*
			 * We cannot remove the buffer with io error from the
			 * committing transaction, because otherwise it would
			 * miss the error and the commit would not abort.
			 */
			if (unlikely(!buffer_uptodate(bh))) {
				ret = -EIO;
				goto no_journal;
			}

			if (jh->b_transaction != NULL) {
				JBUFFER_TRACE(jh, "unfile from commit");
				__journal_temp_unlink_buffer(jh);
				/* It still points to the committing
				 * transaction; move it to this one so
				 * that the refile assert checks are
				 * happy. */
				jh->b_transaction = handle->h_transaction;
			}
			/* The buffer will be refiled below */

		}
		/*
		 * Special case --- the buffer might actually have been
		 * allocated and then immediately deallocated in the previous,
		 * committing transaction, so might still be left on that
		 * transaction's metadata lists.
		 */
		if (jh->b_jlist != BJ_SyncData && jh->b_jlist != BJ_Locked) {
			JBUFFER_TRACE(jh, "not on correct data list: unfile");
			J_ASSERT_JH(jh, jh->b_jlist != BJ_Shadow);
			__journal_temp_unlink_buffer(jh);
			jh->b_transaction = handle->h_transaction;
			JBUFFER_TRACE(jh, "file as data");
			__journal_file_buffer(jh, handle->h_transaction,
						BJ_SyncData);
		}
	} else {
		JBUFFER_TRACE(jh, "not on a transaction");
		__journal_file_buffer(jh, handle->h_transaction, BJ_SyncData);
	}
no_journal:
	spin_unlock(&journal->j_list_lock);
	jbd_unlock_bh_state(bh);
	if (need_brelse) {
		BUFFER_TRACE(bh, "brelse");
		__brelse(bh);
	}
	JBUFFER_TRACE(jh, "exit");
	journal_put_journal_head(jh);
	return ret;
}