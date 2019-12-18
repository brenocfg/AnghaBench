#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ p_dtrace_count; int /*<<< orphan*/ * p_dtrace_helpers; } ;
typedef  TYPE_1__ proc_t ;

/* Variables and functions */
 scalar_t__ DTRACE_LAZY_DOFS_DUPLICATED ; 
 int /*<<< orphan*/  dtrace_fasttrap_fork (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_helpers_fork (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ dtrace_lazy_dofs_duplicate (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_sprlock (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_sprunlock (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_1__*) ; 

void
dtrace_proc_fork(proc_t *parent_proc, proc_t *child_proc, int spawn)
{
	/*
	 * This code applies to new processes who are copying the task
	 * and thread state and address spaces of their parent process.
	 */
	if (!spawn) {
		/*
		 * APPLE NOTE: Solaris does a sprlock() and drops the
		 * proc_lock here. We're cheating a bit and only taking
		 * the p_dtrace_sprlock lock. A full sprlock would
		 * task_suspend the parent.
		 */
		dtrace_sprlock(parent_proc);

		/*
		 * Remove all DTrace tracepoints from the child process. We
		 * need to do this _before_ duplicating USDT providers since
		 * any associated probes may be immediately enabled.
		 */
		if (parent_proc->p_dtrace_count > 0) {
			dtrace_fasttrap_fork(parent_proc, child_proc);
		}

		dtrace_sprunlock(parent_proc);

		/*
		 * Duplicate any lazy dof(s). This must be done while NOT
		 * holding the parent sprlock! Lock ordering is
		 * dtrace_dof_mode_lock, then sprlock.  It is imperative we
		 * always call dtrace_lazy_dofs_duplicate, rather than null
		 * check and call if !NULL. If we NULL test, during lazy dof
		 * faulting we can race with the faulting code and proceed
		 * from here to beyond the helpers copy. The lazy dof
		 * faulting will then fail to copy the helpers to the child
		 * process. We return if we duplicated lazy dofs as a process
		 * can only have one at the same time to avoid a race between
		 * a dtrace client and dtrace_proc_fork where a process would
		 * end up with both lazy dofs and helpers.
		 */
		if (dtrace_lazy_dofs_duplicate(parent_proc, child_proc) == DTRACE_LAZY_DOFS_DUPLICATED) {
			return;
		}

		/*
		 * Duplicate any helper actions and providers if they haven't
		 * already.
		 */
#if !defined(__APPLE__)
		 /*
		 * The SFORKING
		 * we set above informs the code to enable USDT probes that
		 * sprlock() may fail because the child is being forked.
		 */
#endif
		/*
		 * APPLE NOTE: As best I can tell, Apple's sprlock() equivalent
		 * never fails to find the child. We do not set SFORKING.
		 */
		if (parent_proc->p_dtrace_helpers != NULL && dtrace_helpers_fork) {
			(*dtrace_helpers_fork)(parent_proc, child_proc);
		}
	}
}