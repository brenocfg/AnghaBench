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
struct dlm_ctxt {int /*<<< orphan*/ * dlm_thread_task; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_thread ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct dlm_ctxt*,char*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 

int dlm_launch_thread(struct dlm_ctxt *dlm)
{
	mlog(0, "starting dlm thread...\n");

	dlm->dlm_thread_task = kthread_run(dlm_thread, dlm, "dlm_thread");
	if (IS_ERR(dlm->dlm_thread_task)) {
		mlog_errno(PTR_ERR(dlm->dlm_thread_task));
		dlm->dlm_thread_task = NULL;
		return -EINVAL;
	}

	return 0;
}