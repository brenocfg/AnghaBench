#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  p_dtrace_sprlock; int /*<<< orphan*/  p_mlock; } ;
typedef  TYPE_1__ proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FASTTRAP_OBJC_NAME ; 
 int /*<<< orphan*/  FASTTRAP_ONESHOT_NAME ; 
 int /*<<< orphan*/  FASTTRAP_PID_NAME ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  dtrace_ptss_exec_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  fasttrap_provider_retire (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
fasttrap_exec_exit(proc_t *p)
{
	ASSERT(p == current_proc());
	LCK_MTX_ASSERT(&p->p_mlock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&p->p_dtrace_sprlock, LCK_MTX_ASSERT_NOTOWNED);


	/* APPLE NOTE: Okay, the locking here is really odd and needs some
	 * explaining. This method is always called with the proc_lock held.
	 * We must drop the proc_lock before calling fasttrap_provider_retire
	 * to avoid a deadlock when it takes the bucket lock.
	 * 
	 * Next, the dtrace_ptss_exec_exit function requires the sprlock
	 * be held, but not the proc_lock. 
	 *
	 * Finally, we must re-acquire the proc_lock
	 */
	proc_unlock(p);

	/*
	 * We clean up the pid provider for this process here; user-land
	 * static probes are handled by the meta-provider remove entry point.
	 */
	fasttrap_provider_retire(p, FASTTRAP_PID_NAME, 0);

	/*
	 * APPLE NOTE: We also need to remove any aliased providers.
	 * XXX optimization: track which provider types are instantiated
	 * and only retire as needed.
	 */
	fasttrap_provider_retire(p, FASTTRAP_OBJC_NAME, 0);
	fasttrap_provider_retire(p, FASTTRAP_ONESHOT_NAME, 0);

	/*
	 * This should be called after it is no longer possible for a user
	 * thread to execute (potentially dtrace instrumented) instructions.
	 */
	lck_mtx_lock(&p->p_dtrace_sprlock);
	dtrace_ptss_exec_exit(p);
	lck_mtx_unlock(&p->p_dtrace_sprlock);

	proc_lock(p);
}