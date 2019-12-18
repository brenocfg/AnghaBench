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
typedef  scalar_t__ tid_t ;
struct TYPE_5__ {scalar_t__ j_commit_request; TYPE_1__* j_running_transaction; int /*<<< orphan*/  j_commit_sequence; int /*<<< orphan*/  j_wait_commit; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_4__ {scalar_t__ t_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tid_geq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int __jbd2_log_start_commit(journal_t *journal, tid_t target)
{
	/* Return if the txn has already requested to be committed */
	if (journal->j_commit_request == target)
		return 0;

	/*
	 * The only transaction we can possibly wait upon is the
	 * currently running transaction (if it exists).  Otherwise,
	 * the target tid must be an old one.
	 */
	if (journal->j_running_transaction &&
	    journal->j_running_transaction->t_tid == target) {
		/*
		 * We want a new commit: OK, mark the request and wakeup the
		 * commit thread.  We do _not_ do the commit ourselves.
		 */

		journal->j_commit_request = target;
		jbd_debug(1, "JBD: requesting commit %d/%d\n",
			  journal->j_commit_request,
			  journal->j_commit_sequence);
		wake_up(&journal->j_wait_commit);
		return 1;
	} else if (!tid_geq(journal->j_commit_request, target))
		/* This should never happen, but if it does, preserve
		   the evidence before kjournald goes into a loop and
		   increments j_commit_sequence beyond all recognition. */
		WARN(1, "jbd: bad log_start_commit: %u %u %u %u\n",
		     journal->j_commit_request, journal->j_commit_sequence,
		     target, journal->j_running_transaction ? 
		     journal->j_running_transaction->t_tid : 0);
	return 0;
}