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
struct dlm_ctxt {unsigned int name; int /*<<< orphan*/  dlm_worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int DLM_DOMAIN_BACKOFF_MS ; 
 int /*<<< orphan*/  DLM_JOIN_TIMEOUT_MSECS ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dlm_complete_recovery_thread (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_complete_thread (struct dlm_ctxt*) ; 
 int dlm_debug_init (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_debug_shutdown (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_destroy_dlm_worker (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_domain_events ; 
 int dlm_launch_recovery_thread (struct dlm_ctxt*) ; 
 int dlm_launch_thread (struct dlm_ctxt*) ; 
 int dlm_register_domain_handlers (struct dlm_ctxt*) ; 
 int dlm_try_to_join_domain (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_unregister_domain_handlers (struct dlm_ctxt*) ; 
 int jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 unsigned int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_join_domain(struct dlm_ctxt *dlm)
{
	int status;
	unsigned int backoff;
	unsigned int total_backoff = 0;

	BUG_ON(!dlm);

	mlog(0, "Join domain %s\n", dlm->name);

	status = dlm_register_domain_handlers(dlm);
	if (status) {
		mlog_errno(status);
		goto bail;
	}

	status = dlm_debug_init(dlm);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = dlm_launch_thread(dlm);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = dlm_launch_recovery_thread(dlm);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	dlm->dlm_worker = create_singlethread_workqueue("dlm_wq");
	if (!dlm->dlm_worker) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	do {
		status = dlm_try_to_join_domain(dlm);

		/* If we're racing another node to the join, then we
		 * need to back off temporarily and let them
		 * complete. */
#define	DLM_JOIN_TIMEOUT_MSECS	90000
		if (status == -EAGAIN) {
			if (signal_pending(current)) {
				status = -ERESTARTSYS;
				goto bail;
			}

			if (total_backoff >
			    msecs_to_jiffies(DLM_JOIN_TIMEOUT_MSECS)) {
				status = -ERESTARTSYS;
				mlog(ML_NOTICE, "Timed out joining dlm domain "
				     "%s after %u msecs\n", dlm->name,
				     jiffies_to_msecs(total_backoff));
				goto bail;
			}

			/*
			 * <chip> After you!
			 * <dale> No, after you!
			 * <chip> I insist!
			 * <dale> But you first!
			 * ...
			 */
			backoff = (unsigned int)(jiffies & 0x3);
			backoff *= DLM_DOMAIN_BACKOFF_MS;
			total_backoff += backoff;
			mlog(0, "backoff %d\n", backoff);
			msleep(backoff);
		}
	} while (status == -EAGAIN);

	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = 0;
bail:
	wake_up(&dlm_domain_events);

	if (status) {
		dlm_unregister_domain_handlers(dlm);
		dlm_debug_shutdown(dlm);
		dlm_complete_thread(dlm);
		dlm_complete_recovery_thread(dlm);
		dlm_destroy_dlm_worker(dlm);
	}

	return status;
}