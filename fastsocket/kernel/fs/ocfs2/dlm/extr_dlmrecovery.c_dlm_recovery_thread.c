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
struct dlm_ctxt {int /*<<< orphan*/  dlm_reco_thread_wq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RECO_THREAD_TIMEOUT_MS ; 
 int EAGAIN ; 
 int dlm_do_recovery (struct dlm_ctxt*) ; 
 scalar_t__ dlm_joined (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int dlm_recovery_thread(void *data)
{
	int status;
	struct dlm_ctxt *dlm = data;
	unsigned long timeout = msecs_to_jiffies(DLM_RECO_THREAD_TIMEOUT_MS);

	mlog(0, "dlm thread running for %s...\n", dlm->name);

	while (!kthread_should_stop()) {
		if (dlm_joined(dlm)) {
			status = dlm_do_recovery(dlm);
			if (status == -EAGAIN) {
				/* do not sleep, recheck immediately. */
				continue;
			}
			if (status < 0)
				mlog_errno(status);
		}

		wait_event_interruptible_timeout(dlm->dlm_reco_thread_wq,
						 kthread_should_stop(),
						 timeout);
	}

	mlog(0, "quitting DLM recovery thread\n");
	return 0;
}