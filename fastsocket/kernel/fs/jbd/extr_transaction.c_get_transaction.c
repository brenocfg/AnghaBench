#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ t_expires; int /*<<< orphan*/  t_handle_lock; scalar_t__ t_tid; int /*<<< orphan*/  t_start_time; int /*<<< orphan*/  t_state; TYPE_2__* t_journal; } ;
typedef  TYPE_1__ transaction_t ;
struct TYPE_9__ {int /*<<< orphan*/  expires; } ;
struct TYPE_8__ {TYPE_1__* j_running_transaction; TYPE_6__ j_commit_timer; scalar_t__ j_commit_interval; int /*<<< orphan*/  j_transaction_sequence; } ;
typedef  TYPE_2__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  J_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_RUNNING ; 
 int /*<<< orphan*/  add_timer (TYPE_6__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  round_jiffies_up (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static transaction_t *
get_transaction(journal_t *journal, transaction_t *transaction)
{
	transaction->t_journal = journal;
	transaction->t_state = T_RUNNING;
	transaction->t_start_time = ktime_get();
	transaction->t_tid = journal->j_transaction_sequence++;
	transaction->t_expires = jiffies + journal->j_commit_interval;
	spin_lock_init(&transaction->t_handle_lock);

	/* Set up the commit timer for the new transaction. */
	journal->j_commit_timer.expires =
				round_jiffies_up(transaction->t_expires);
	add_timer(&journal->j_commit_timer);

	J_ASSERT(journal->j_running_transaction == NULL);
	journal->j_running_transaction = transaction;

	return transaction;
}