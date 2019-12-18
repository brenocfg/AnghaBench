#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct jbd2_inode {int /*<<< orphan*/ * i_transaction; int /*<<< orphan*/  i_list; int /*<<< orphan*/  i_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/ * j_committing_transaction; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_6__ {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_BIT (TYPE_2__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __JI_COMMIT_RUNNING ; 
 int /*<<< orphan*/ * bit_waitqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ wait ; 

void jbd2_journal_release_jbd_inode(journal_t *journal,
				    struct jbd2_inode *jinode)
{
	int writeout = 0;

	if (!journal)
		return;
restart:
	spin_lock(&journal->j_list_lock);
	/* Is commit writing out inode - we have to wait */
	if (test_bit(__JI_COMMIT_RUNNING, &jinode->i_flags)) {
		wait_queue_head_t *wq;
		DEFINE_WAIT_BIT(wait, &jinode->i_flags, __JI_COMMIT_RUNNING);
		smp_mb();
		wq = bit_waitqueue(&jinode->i_flags, __JI_COMMIT_RUNNING);
		prepare_to_wait(wq, &wait.wait, TASK_UNINTERRUPTIBLE);
		spin_unlock(&journal->j_list_lock);
		schedule();
		finish_wait(wq, &wait.wait);
		goto restart;
	}

	/* Do we need to wait for data writeback? */
	if (journal->j_committing_transaction == jinode->i_transaction)
		writeout = 1;
	if (jinode->i_transaction) {
		list_del(&jinode->i_list);
		jinode->i_transaction = NULL;
	}
	spin_unlock(&journal->j_list_lock);
}