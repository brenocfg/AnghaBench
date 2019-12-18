#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ t_tid; int /*<<< orphan*/  t_expires; } ;
typedef  TYPE_1__ transaction_t ;
struct TYPE_5__ {int j_flags; scalar_t__ j_commit_sequence; scalar_t__ j_commit_request; int /*<<< orphan*/  j_wait_done_commit; int /*<<< orphan*/ * j_task; int /*<<< orphan*/  j_commit_timer; int /*<<< orphan*/  j_state_lock; TYPE_1__* j_running_transaction; int /*<<< orphan*/  j_wait_commit; } ;
typedef  TYPE_2__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int JBD2_UNMOUNT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  commit_timeout ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ freezing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_commit_transaction (TYPE_2__*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,...) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refrigerator () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kjournald2(void *arg)
{
	journal_t *journal = arg;
	transaction_t *transaction;

	/*
	 * Set up an interval timer which can be used to trigger a commit wakeup
	 * after the commit interval expires
	 */
	setup_timer(&journal->j_commit_timer, commit_timeout,
			(unsigned long)current);

	/* Record that the journal thread is running */
	journal->j_task = current;
	wake_up(&journal->j_wait_done_commit);

	/*
	 * And now, wait forever for commit wakeup events.
	 */
	spin_lock(&journal->j_state_lock);

loop:
	if (journal->j_flags & JBD2_UNMOUNT)
		goto end_loop;

	jbd_debug(1, "commit_sequence=%d, commit_request=%d\n",
		journal->j_commit_sequence, journal->j_commit_request);

	if (journal->j_commit_sequence != journal->j_commit_request) {
		jbd_debug(1, "OK, requests differ\n");
		spin_unlock(&journal->j_state_lock);
		del_timer_sync(&journal->j_commit_timer);
		jbd2_journal_commit_transaction(journal);
		spin_lock(&journal->j_state_lock);
		goto loop;
	}

	wake_up(&journal->j_wait_done_commit);
	if (freezing(current)) {
		/*
		 * The simpler the better. Flushing journal isn't a
		 * good idea, because that depends on threads that may
		 * be already stopped.
		 */
		jbd_debug(1, "Now suspending kjournald2\n");
		spin_unlock(&journal->j_state_lock);
		refrigerator();
		spin_lock(&journal->j_state_lock);
	} else {
		/*
		 * We assume on resume that commits are already there,
		 * so we don't sleep
		 */
		DEFINE_WAIT(wait);
		int should_sleep = 1;

		prepare_to_wait(&journal->j_wait_commit, &wait,
				TASK_INTERRUPTIBLE);
		if (journal->j_commit_sequence != journal->j_commit_request)
			should_sleep = 0;
		transaction = journal->j_running_transaction;
		if (transaction && time_after_eq(jiffies,
						transaction->t_expires))
			should_sleep = 0;
		if (journal->j_flags & JBD2_UNMOUNT)
			should_sleep = 0;
		if (should_sleep) {
			spin_unlock(&journal->j_state_lock);
			schedule();
			spin_lock(&journal->j_state_lock);
		}
		finish_wait(&journal->j_wait_commit, &wait);
	}

	jbd_debug(1, "kjournald2 wakes\n");

	/*
	 * Were we woken up by a commit wakeup event?
	 */
	transaction = journal->j_running_transaction;
	if (transaction && time_after_eq(jiffies, transaction->t_expires)) {
		journal->j_commit_request = transaction->t_tid;
		jbd_debug(1, "woke because of timeout\n");
	}
	goto loop;

end_loop:
	spin_unlock(&journal->j_state_lock);
	del_timer_sync(&journal->j_commit_timer);
	journal->j_task = NULL;
	wake_up(&journal->j_wait_done_commit);
	jbd_debug(1, "Journal thread exiting.\n");
	return 0;
}