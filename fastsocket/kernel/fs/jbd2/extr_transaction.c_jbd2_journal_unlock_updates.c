#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ j_barrier_count; int /*<<< orphan*/  j_wait_transaction_locked; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_barrier; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void jbd2_journal_unlock_updates (journal_t *journal)
{
	J_ASSERT(journal->j_barrier_count != 0);

	mutex_unlock(&journal->j_barrier);
	spin_lock(&journal->j_state_lock);
	--journal->j_barrier_count;
	spin_unlock(&journal->j_state_lock);
	wake_up(&journal->j_wait_transaction_locked);
}