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
struct dlm_ls {scalar_t__ ls_recover_begin; scalar_t__ ls_recover_status; int /*<<< orphan*/  ls_in_recovery; int /*<<< orphan*/  ls_recv_active; int /*<<< orphan*/  ls_recover_lock; int /*<<< orphan*/  ls_recover_seq; int /*<<< orphan*/  ls_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSFL_RECOVERY_STOP ; 
 int /*<<< orphan*/  LSFL_RUNNING ; 
 int /*<<< orphan*/  dlm_recoverd_resume (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_recoverd_suspend (struct dlm_ls*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dlm_ls_stop(struct dlm_ls *ls)
{
	int new;

	/*
	 * Prevent dlm_recv from being in the middle of something when we do
	 * the stop.  This includes ensuring dlm_recv isn't processing a
	 * recovery message (rcom), while dlm_recoverd is aborting and
	 * resetting things from an in-progress recovery.  i.e. we want
	 * dlm_recoverd to abort its recovery without worrying about dlm_recv
	 * processing an rcom at the same time.  Stopping dlm_recv also makes
	 * it easy for dlm_receive_message() to check locking stopped and add a
	 * message to the requestqueue without races.
	 */

	down_write(&ls->ls_recv_active);

	/*
	 * Abort any recovery that's in progress (see RECOVERY_STOP,
	 * dlm_recovery_stopped()) and tell any other threads running in the
	 * dlm to quit any processing (see RUNNING, dlm_locking_stopped()).
	 */

	spin_lock(&ls->ls_recover_lock);
	set_bit(LSFL_RECOVERY_STOP, &ls->ls_flags);
	new = test_and_clear_bit(LSFL_RUNNING, &ls->ls_flags);
	ls->ls_recover_seq++;
	spin_unlock(&ls->ls_recover_lock);

	/*
	 * Let dlm_recv run again, now any normal messages will be saved on the
	 * requestqueue for later.
	 */

	up_write(&ls->ls_recv_active);

	/*
	 * This in_recovery lock does two things:
	 * 1) Keeps this function from returning until all threads are out
	 *    of locking routines and locking is truely stopped.
	 * 2) Keeps any new requests from being processed until it's unlocked
	 *    when recovery is complete.
	 */

	if (new)
		down_write(&ls->ls_in_recovery);

	/*
	 * The recoverd suspend/resume makes sure that dlm_recoverd (if
	 * running) has noticed RECOVERY_STOP above and quit processing the
	 * previous recovery.
	 */

	dlm_recoverd_suspend(ls);
	ls->ls_recover_status = 0;
	dlm_recoverd_resume(ls);

	if (!ls->ls_recover_begin)
		ls->ls_recover_begin = jiffies;
	return 0;
}