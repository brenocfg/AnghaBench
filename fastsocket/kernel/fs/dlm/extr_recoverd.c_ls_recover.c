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
struct dlm_recover {scalar_t__ seq; } ;
struct dlm_ls {int /*<<< orphan*/  ls_recoverd_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RS_DONE ; 
 int /*<<< orphan*/  DLM_RS_LOCKS ; 
 int /*<<< orphan*/  dlm_adjust_timeouts (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_astd_resume () ; 
 int /*<<< orphan*/  dlm_astd_suspend () ; 
 int /*<<< orphan*/  dlm_astd_wake () ; 
 int /*<<< orphan*/  dlm_clear_members_gone (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_clear_toss_list (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_create_root_list (struct dlm_ls*) ; 
 scalar_t__ dlm_no_directory (struct dlm_ls*) ; 
 int dlm_process_requestqueue (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_purge_requestqueue (struct dlm_ls*) ; 
 int dlm_recover_directory (struct dlm_ls*) ; 
 int dlm_recover_directory_wait (struct dlm_ls*) ; 
 int dlm_recover_done_wait (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_recover_grant (struct dlm_ls*) ; 
 int dlm_recover_locks (struct dlm_ls*) ; 
 int dlm_recover_locks_wait (struct dlm_ls*) ; 
 int dlm_recover_masters (struct dlm_ls*) ; 
 int dlm_recover_members (struct dlm_ls*,struct dlm_recover*,int*) ; 
 int /*<<< orphan*/  dlm_recover_purge (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_recover_rsbs (struct dlm_ls*) ; 
 int dlm_recover_waiters_post (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_recover_waiters_pre (struct dlm_ls*) ; 
 int dlm_recovery_stopped (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_release_root_list (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_set_recover_status (struct dlm_ls*,int /*<<< orphan*/ ) ; 
 int enable_locking (struct dlm_ls*,scalar_t__) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ls_recover(struct dlm_ls *ls, struct dlm_recover *rv)
{
	unsigned long start;
	int error, neg = 0;

	log_debug(ls, "recover %llx", (unsigned long long)rv->seq);

	mutex_lock(&ls->ls_recoverd_active);

	/*
	 * Suspending and resuming dlm_astd ensures that no lkb's from this ls
	 * will be processed by dlm_astd during recovery.
	 */

	dlm_astd_suspend();
	dlm_astd_resume();

	/*
	 * Free non-master tossed rsb's.  Master rsb's are kept on toss
	 * list and put on root list to be included in resdir recovery.
	 */

	dlm_clear_toss_list(ls);

	/*
	 * This list of root rsb's will be the basis of most of the recovery
	 * routines.
	 */

	dlm_create_root_list(ls);

	/*
	 * Add or remove nodes from the lockspace's ls_nodes list.
	 * Also waits for all nodes to complete dlm_recover_members.
	 */

	error = dlm_recover_members(ls, rv, &neg);
	if (error) {
		log_debug(ls, "recover_members failed %d", error);
		goto fail;
	}
	start = jiffies;

	/*
	 * Rebuild our own share of the directory by collecting from all other
	 * nodes their master rsb names that hash to us.
	 */

	error = dlm_recover_directory(ls);
	if (error) {
		log_debug(ls, "recover_directory failed %d", error);
		goto fail;
	}

	/*
	 * Wait for all nodes to complete directory rebuild.
	 */

	error = dlm_recover_directory_wait(ls);
	if (error) {
		log_debug(ls, "recover_directory_wait failed %d", error);
		goto fail;
	}

	/*
	 * We may have outstanding operations that are waiting for a reply from
	 * a failed node.  Mark these to be resent after recovery.  Unlock and
	 * cancel ops can just be completed.
	 */

	dlm_recover_waiters_pre(ls);

	error = dlm_recovery_stopped(ls);
	if (error)
		goto fail;

	if (neg || dlm_no_directory(ls)) {
		/*
		 * Clear lkb's for departed nodes.
		 */

		dlm_recover_purge(ls);

		/*
		 * Get new master nodeid's for rsb's that were mastered on
		 * departed nodes.
		 */

		error = dlm_recover_masters(ls);
		if (error) {
			log_debug(ls, "recover_masters failed %d", error);
			goto fail;
		}

		/*
		 * Send our locks on remastered rsb's to the new masters.
		 */

		error = dlm_recover_locks(ls);
		if (error) {
			log_debug(ls, "recover_locks failed %d", error);
			goto fail;
		}

		error = dlm_recover_locks_wait(ls);
		if (error) {
			log_debug(ls, "recover_locks_wait failed %d", error);
			goto fail;
		}

		/*
		 * Finalize state in master rsb's now that all locks can be
		 * checked.  This includes conversion resolution and lvb
		 * settings.
		 */

		dlm_recover_rsbs(ls);
	} else {
		/*
		 * Other lockspace members may be going through the "neg" steps
		 * while also adding us to the lockspace, in which case they'll
		 * be doing the recover_locks (RS_LOCKS) barrier.
		 */
		dlm_set_recover_status(ls, DLM_RS_LOCKS);

		error = dlm_recover_locks_wait(ls);
		if (error) {
			log_debug(ls, "recover_locks_wait failed %d", error);
			goto fail;
		}
	}

	dlm_release_root_list(ls);

	/*
	 * Purge directory-related requests that are saved in requestqueue.
	 * All dir requests from before recovery are invalid now due to the dir
	 * rebuild and will be resent by the requesting nodes.
	 */

	dlm_purge_requestqueue(ls);

	dlm_set_recover_status(ls, DLM_RS_DONE);
	error = dlm_recover_done_wait(ls);
	if (error) {
		log_debug(ls, "recover_done_wait failed %d", error);
		goto fail;
	}

	dlm_clear_members_gone(ls);

	dlm_adjust_timeouts(ls);

	error = enable_locking(ls, rv->seq);
	if (error) {
		log_debug(ls, "enable_locking failed %d", error);
		goto fail;
	}

	error = dlm_process_requestqueue(ls);
	if (error) {
		log_debug(ls, "process_requestqueue failed %d", error);
		goto fail;
	}

	error = dlm_recover_waiters_post(ls);
	if (error) {
		log_debug(ls, "recover_waiters_post failed %d", error);
		goto fail;
	}

	dlm_recover_grant(ls);

	dlm_astd_wake();

	log_debug(ls, "recover %llx done: %u ms",
		  (unsigned long long)rv->seq,
		  jiffies_to_msecs(jiffies - start));
	mutex_unlock(&ls->ls_recoverd_active);

	return 0;

 fail:
	dlm_release_root_list(ls);
	log_debug(ls, "recover %llx error %d",
		  (unsigned long long)rv->seq, error);
	mutex_unlock(&ls->ls_recoverd_active);
	return error;
}