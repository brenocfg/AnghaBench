#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_15__ {struct TYPE_15__* p_stats; struct TYPE_15__* p_sigacts; int /*<<< orphan*/  p_rcall; int /*<<< orphan*/  p_ucred; int /*<<< orphan*/  p_slock; int /*<<< orphan*/  p_dtrace_sprlock; int /*<<< orphan*/  p_ucred_mlock; int /*<<< orphan*/  p_fdmlock; int /*<<< orphan*/  p_mlock; int /*<<< orphan*/ * p_textvp; scalar_t__ vm_shm; int /*<<< orphan*/ * p_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SESSION_PROCEXIT (TYPE_1__*) ; 
 int /*<<< orphan*/  FREE_ZONE (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PROC ; 
 int /*<<< orphan*/  M_PSTATS ; 
 int /*<<< orphan*/  M_SIGACTS ; 
 int /*<<< orphan*/  fdfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nprocs ; 
 int /*<<< orphan*/  p_hash ; 
 int /*<<< orphan*/  persona_proc_drop (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_checkdeadrefs (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_fdmlock_grp ; 
 int /*<<< orphan*/  proc_lck_grp ; 
 int /*<<< orphan*/  proc_limitdrop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  proc_mlock_grp ; 
 int /*<<< orphan*/  proc_signalend (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_slock_grp ; 
 int /*<<< orphan*/  proc_transend (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_ucred_mlock_grp ; 
 int /*<<< orphan*/  pth_proc_hashdelete (TYPE_1__*) ; 
 int /*<<< orphan*/  shmexec (TYPE_1__*) ; 
 int /*<<< orphan*/  stopprofclock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_call_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_rele (int /*<<< orphan*/ *) ; 

void
forkproc_free(proc_t p)
{
#if CONFIG_PERSONAS
	persona_proc_drop(p);
#endif /* CONFIG_PERSONAS */

#if PSYNCH
	pth_proc_hashdelete(p);
#endif /* PSYNCH */

	/* We held signal and a transition locks; drop them */
	proc_signalend(p, 0);
	proc_transend(p, 0);

	/*
	 * If we have our own copy of the resource limits structure, we
	 * need to free it.  If it's a shared copy, we need to drop our
	 * reference on it.
	 */
	proc_limitdrop(p, 0);
	p->p_limit = NULL;

#if SYSV_SHM
	/* Need to drop references to the shared memory segment(s), if any */
	if (p->vm_shm) {
		/*
		 * Use shmexec(): we have no address space, so no mappings
		 *
		 * XXX Yes, the routine is badly named.
		 */
		shmexec(p);
	}
#endif

	/* Need to undo the effects of the fdcopy(), if any */
	fdfree(p);

	/*
	 * Drop the reference on a text vnode pointer, if any
	 * XXX This code is broken in forkproc(); see <rdar://4256419>;
	 * XXX if anyone ever uses this field, we will be extremely unhappy.
	 */
	if (p->p_textvp) {
		vnode_rele(p->p_textvp);
		p->p_textvp = NULL;
	}

	/* Stop the profiling clock */
	stopprofclock(p);

	/* Update the audit session proc count */
	AUDIT_SESSION_PROCEXIT(p);

#if CONFIG_FINE_LOCK_GROUPS
	lck_mtx_destroy(&p->p_mlock, proc_mlock_grp);
	lck_mtx_destroy(&p->p_fdmlock, proc_fdmlock_grp);
	lck_mtx_destroy(&p->p_ucred_mlock, proc_ucred_mlock_grp);
#if CONFIG_DTRACE
	lck_mtx_destroy(&p->p_dtrace_sprlock, proc_lck_grp);
#endif
	lck_spin_destroy(&p->p_slock, proc_slock_grp);
#else /* CONFIG_FINE_LOCK_GROUPS */
	lck_mtx_destroy(&p->p_mlock, proc_lck_grp);
	lck_mtx_destroy(&p->p_fdmlock, proc_lck_grp);
	lck_mtx_destroy(&p->p_ucred_mlock, proc_lck_grp);
#if CONFIG_DTRACE
	lck_mtx_destroy(&p->p_dtrace_sprlock, proc_lck_grp);
#endif
	lck_spin_destroy(&p->p_slock, proc_lck_grp);
#endif /* CONFIG_FINE_LOCK_GROUPS */

	/* Release the credential reference */
	kauth_cred_unref(&p->p_ucred);

	proc_list_lock();
	/* Decrement the count of processes in the system */
	nprocs--;

	/* Take it out of process hash */
	LIST_REMOVE(p, p_hash);

	proc_list_unlock();

	thread_call_free(p->p_rcall);

	/* Free allocated memory */
	FREE_ZONE(p->p_sigacts, sizeof *p->p_sigacts, M_SIGACTS);
	p->p_sigacts = NULL;
	FREE_ZONE(p->p_stats, sizeof *p->p_stats, M_PSTATS);
	p->p_stats = NULL;

	proc_checkdeadrefs(p);
	FREE_ZONE(p, sizeof *p, M_PROC);
}