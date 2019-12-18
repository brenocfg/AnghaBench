#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int t_need_data_flush; int /*<<< orphan*/  t_inode_list; int /*<<< orphan*/  t_tid; TYPE_3__* t_journal; } ;
typedef  TYPE_2__ transaction_t ;
struct jbd2_inode {int /*<<< orphan*/  i_list; TYPE_2__* i_transaction; TYPE_2__* i_next_transaction; TYPE_1__* i_vfs_inode; } ;
struct TYPE_9__ {int /*<<< orphan*/  j_list_lock; TYPE_2__* j_committing_transaction; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_10__ {TYPE_2__* h_transaction; } ;
typedef  TYPE_4__ handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 scalar_t__ is_handle_aborted (TYPE_4__*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int jbd2_journal_file_inode(handle_t *handle, struct jbd2_inode *jinode)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal = transaction->t_journal;

	if (is_handle_aborted(handle))
		return -EIO;

	jbd_debug(4, "Adding inode %lu, tid:%d\n", jinode->i_vfs_inode->i_ino,
			transaction->t_tid);

	/*
	 * First check whether inode isn't already on the transaction's
	 * lists without taking the lock. Note that this check is safe
	 * without the lock as we cannot race with somebody removing inode
	 * from the transaction. The reason is that we remove inode from the
	 * transaction only in journal_release_jbd_inode() and when we commit
	 * the transaction. We are guarded from the first case by holding
	 * a reference to the inode. We are safe against the second case
	 * because if jinode->i_transaction == transaction, commit code
	 * cannot touch the transaction because we hold reference to it,
	 * and if jinode->i_next_transaction == transaction, commit code
	 * will only file the inode where we want it.
	 */
	if (jinode->i_transaction == transaction ||
	    jinode->i_next_transaction == transaction)
		return 0;

	spin_lock(&journal->j_list_lock);

	if (jinode->i_transaction == transaction ||
	    jinode->i_next_transaction == transaction)
		goto done;

	/*
	 * We only ever set this variable to 1 so the test is safe. Since
	 * t_need_data_flush is likely to be set, we do the test to save some
	 * cacheline bouncing
	 */
	if (!transaction->t_need_data_flush)
		transaction->t_need_data_flush = 1;
	/* On some different transaction's list - should be
	 * the committing one */
	if (jinode->i_transaction) {
		J_ASSERT(jinode->i_next_transaction == NULL);
		J_ASSERT(jinode->i_transaction ==
					journal->j_committing_transaction);
		jinode->i_next_transaction = transaction;
		goto done;
	}
	/* Not on any transaction list... */
	J_ASSERT(!jinode->i_next_transaction);
	jinode->i_transaction = transaction;
	list_add(&jinode->i_list, &transaction->t_inode_list);
done:
	spin_unlock(&journal->j_list_lock);

	return 0;
}