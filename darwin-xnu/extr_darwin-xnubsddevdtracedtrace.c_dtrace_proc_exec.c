#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ p_dtrace_probes; int /*<<< orphan*/ * p_dtrace_helpers; } ;
typedef  TYPE_1__ proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  dtrace_fasttrap_exec_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_helpers_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_lazy_dofs_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_set_thread_predcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

void
dtrace_proc_exec(proc_t *p)
{
	/*
	 * Invalidate any predicate evaluation already cached for this thread by DTrace.
	 * That's because we've just stored to p_comm and DTrace refers to that when it
	 * evaluates the "execname" special variable. uid and gid may have changed as well.
	 */
	dtrace_set_thread_predcache(current_thread(), 0);

	/*
	 * Free any outstanding lazy dof entries. It is imperative we
	 * always call dtrace_lazy_dofs_destroy, rather than null check
	 * and call if !NULL. If we NULL test, during lazy dof faulting
	 * we can race with the faulting code and proceed from here to
	 * beyond the helpers cleanup. The lazy dof faulting will then
	 * install new helpers which no longer belong to this process!
	 */
	dtrace_lazy_dofs_destroy(p);


	/*
	 * Clean up any DTrace helpers for the process.
	 */
	if (p->p_dtrace_helpers != NULL && dtrace_helpers_cleanup) {
		(*dtrace_helpers_cleanup)(p);
	}

	/*
	 * Cleanup the DTrace provider associated with this process.
	 */
	proc_lock(p);
	if (p->p_dtrace_probes && dtrace_fasttrap_exec_ptr) {
		(*dtrace_fasttrap_exec_ptr)(p);
	}
	proc_unlock(p);
}