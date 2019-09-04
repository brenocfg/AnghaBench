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
struct uthread {scalar_t__ uu_exit_reason; } ;
struct task {int dummy; } ;
typedef  int /*<<< orphan*/ * proc_t ;
typedef  scalar_t__ os_reason_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ OS_REASON_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ get_bsdtask_info (struct task*) ; 
 struct uthread* get_bsdthread_info (void*) ; 
 struct task* get_threadtask (void*) ; 
 int /*<<< orphan*/  os_reason_free (scalar_t__) ; 
 int /*<<< orphan*/  proc_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_unlock (int /*<<< orphan*/ *) ; 

void
set_thread_exit_reason(void *th, void *reason, boolean_t proc_locked)
{
	struct uthread *targ_uth = get_bsdthread_info(th);
	struct task *targ_task = NULL;
	proc_t targ_proc = NULL;

	os_reason_t exit_reason = (os_reason_t)reason;

	if (exit_reason == OS_REASON_NULL)
		return;

	if (!proc_locked) {
		targ_task = get_threadtask(th);
		targ_proc = (proc_t)(get_bsdtask_info(targ_task));

		proc_lock(targ_proc);
	}

	if (targ_uth->uu_exit_reason == OS_REASON_NULL) {
		targ_uth->uu_exit_reason = exit_reason;
	} else {
		/* The caller expects that we drop a reference on the exit reason */
		os_reason_free(exit_reason);
	}

	if (!proc_locked) {
		assert(targ_proc != NULL);
		proc_unlock(targ_proc);
	}
}