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
 int /*<<< orphan*/  ML_KTHREAD ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 

void dlm_complete_thread(struct dlm_ctxt *dlm)
{
	if (dlm->dlm_thread_task) {
		mlog(ML_KTHREAD, "waiting for dlm thread to exit\n");
		kthread_stop(dlm->dlm_thread_task);
		dlm->dlm_thread_task = NULL;
	}
}