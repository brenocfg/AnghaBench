#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* proc_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_23__ {int p_xstat; int si_status; int p_flag; char* p_comm; int /*<<< orphan*/  p_slock; int /*<<< orphan*/  p_dtrace_sprlock; int /*<<< orphan*/  p_fdmlock; int /*<<< orphan*/  p_ucred_mlock; int /*<<< orphan*/  p_mlock; int /*<<< orphan*/  p_listflag; int /*<<< orphan*/  p_stat; int /*<<< orphan*/  p_children; int /*<<< orphan*/  p_childrencnt; int /*<<< orphan*/  p_ucred; int /*<<< orphan*/  p_exit_reason; struct TYPE_23__* p_ru; int /*<<< orphan*/  ri; TYPE_1__* p_stats; int /*<<< orphan*/  ru; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  si_pid; scalar_t__ p_oppid; } ;
struct TYPE_22__ {int /*<<< orphan*/  ri_child; int /*<<< orphan*/  p_cru; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SESSION_PROCEXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  CLD_CONTINUED ; 
 int /*<<< orphan*/  FREE_ZONE (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PROC ; 
 int /*<<< orphan*/  M_ZOMBIE ; 
 int NOTE_EXIT ; 
 int NOTE_REAP ; 
 TYPE_2__* PROC_NULL ; 
 int /*<<< orphan*/  P_LIST_DEADPARENT ; 
 int /*<<< orphan*/  P_LIST_INHASH ; 
 int /*<<< orphan*/  P_LIST_WAITING ; 
 int P_NOCLDWAIT ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  chgproccnt (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* initproc ; 
 int /*<<< orphan*/  kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leavepgrp (TYPE_2__*) ; 
 int /*<<< orphan*/  nprocs ; 
 int /*<<< orphan*/  os_reason_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_hash ; 
 int /*<<< orphan*/  p_list ; 
 int /*<<< orphan*/  p_sibling ; 
 int /*<<< orphan*/  persona_proc_drop (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  proc_checkdeadrefs (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_fdmlock_grp ; 
 TYPE_2__* proc_find (scalar_t__) ; 
 int /*<<< orphan*/  proc_knote (TYPE_2__*,int) ; 
 int /*<<< orphan*/  proc_knote_drain (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_lck_grp ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  proc_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_mlock_grp ; 
 int /*<<< orphan*/  proc_rele (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_reparentlocked (TYPE_2__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_slock_grp ; 
 int /*<<< orphan*/  proc_ucred_mlock_grp ; 
 int /*<<< orphan*/  proc_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  psignal (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ruadd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_rusage_info_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
reap_child_locked(proc_t parent, proc_t child, int deadparent, int reparentedtoinit, int locked, int droplock)
{
	proc_t trace_parent = PROC_NULL;	/* Traced parent process, if tracing */

	if (locked == 1)
		proc_list_unlock();
	
	/*
	 * If we got the child via a ptrace 'attach',
	 * we need to give it back to the old parent.
	 *
	 * Exception: someone who has been reparented to launchd before being
	 * ptraced can simply be reaped, refer to radar 5677288
	 * 	p_oppid 		 -> ptraced
	 * 	trace_parent == initproc -> away from launchd
	 * 	reparentedtoinit	 -> came to launchd by reparenting
	 */
	if (child->p_oppid) {
		int knote_hint;
		pid_t oppid;

		proc_lock(child);
		oppid = child->p_oppid;
		child->p_oppid = 0;
		knote_hint = NOTE_EXIT | (child->p_xstat & 0xffff);
		proc_unlock(child);

		if ((trace_parent = proc_find(oppid))
			&& !((trace_parent == initproc) && reparentedtoinit)) {
				
			if (trace_parent != initproc) {
				/* 
				 * proc internal fileds  and p_ucred usage safe 
				 * here as child is dead and is not reaped or 
				 * reparented yet 
				 */
				proc_lock(trace_parent);
				trace_parent->si_pid = child->p_pid;
				trace_parent->si_status = child->p_xstat;
				trace_parent->si_code = CLD_CONTINUED;
				trace_parent->si_uid = kauth_cred_getruid(child->p_ucred);
				proc_unlock(trace_parent);
			}
			proc_reparentlocked(child, trace_parent, 1, 0);
			
			/* resend knote to original parent (and others) after reparenting */
			proc_knote(child, knote_hint);
			
			psignal(trace_parent, SIGCHLD);
			proc_list_lock();
			wakeup((caddr_t)trace_parent);
			child->p_listflag &= ~P_LIST_WAITING;
			wakeup(&child->p_stat);
			proc_list_unlock();
			proc_rele(trace_parent);
			if ((locked == 1) && (droplock == 0))
				proc_list_lock();
			return (0);
		}

		/*
		 * If we can't reparent (e.g. the original parent exited while child was being debugged, or
		 * original parent is the same as the debugger currently exiting), we still need to satisfy
		 * the knote lifecycle for other observers on the system. While the debugger was attached,
		 * the NOTE_EXIT would not have been broadcast during initial child termination.
		 */
		proc_knote(child, knote_hint);

		if (trace_parent != PROC_NULL) {
			proc_rele(trace_parent);
		}
	}
	
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
	proc_knote(child, NOTE_REAP);
#pragma clang diagnostic pop

	proc_knote_drain(child);

	child->p_xstat = 0;
	if (child->p_ru) {
		proc_lock(parent);
#if 3839178
		/*
		 * If the parent is ignoring SIGCHLD, then POSIX requires
		 * us to not add the resource usage to the parent process -
		 * we are only going to hand it off to init to get reaped.
		 * We should contest the standard in this case on the basis
		 * of RLIMIT_CPU.
		 */
		if (!(parent->p_flag & P_NOCLDWAIT))
#endif	/* 3839178 */
			ruadd(&parent->p_stats->p_cru, &child->p_ru->ru);
		update_rusage_info_child(&parent->p_stats->ri_child, &child->p_ru->ri);
		proc_unlock(parent);
		FREE_ZONE(child->p_ru, sizeof *child->p_ru, M_ZOMBIE);
		child->p_ru = NULL;
	} else {
		printf("Warning : lost p_ru for %s\n", child->p_comm);
	}

	AUDIT_SESSION_PROCEXIT(child);

	/*
	 * Decrement the count of procs running with this uid.
	 * p_ucred usage is safe here as it is an exited process.
	 * and refernce is dropped after these calls down below
	 * (locking protection is provided by list lock held in chgproccnt)
	 */
#if CONFIG_PERSONAS
	/*
	 * persona_proc_drop calls chgproccnt(-1) on the persona uid,
	 * and (+1) on the child->p_ucred uid
	 */
	persona_proc_drop(child);
#endif
	(void)chgproccnt(kauth_cred_getruid(child->p_ucred), -1);

	os_reason_free(child->p_exit_reason);

	/*
	 * Free up credentials.
	 */
	if (IS_VALID_CRED(child->p_ucred)) {
		kauth_cred_unref(&child->p_ucred);
	}

	/*  XXXX Note NOT SAFE TO USE p_ucred from this point onwards */

	/*
	 * Finally finished with old proc entry.
	 * Unlink it from its process group and free it.
	 */
	leavepgrp(child);

	proc_list_lock();
	LIST_REMOVE(child, p_list);	/* off zombproc */
	parent->p_childrencnt--;
	LIST_REMOVE(child, p_sibling);
	/* If there are no more children wakeup parent */
	if ((deadparent != 0) && (LIST_EMPTY(&parent->p_children)))
		wakeup((caddr_t)parent);	/* with list lock held */
	child->p_listflag &= ~P_LIST_WAITING;
	wakeup(&child->p_stat);

	/* Take it out of process hash */
	LIST_REMOVE(child, p_hash);
	child->p_listflag &= ~P_LIST_INHASH;
	proc_checkdeadrefs(child);
	nprocs--;

	if (deadparent) {
		/*
		 * If a child zombie is being reaped because its parent
		 * is exiting, make sure we update the list flag
		 */
		child->p_listflag |= P_LIST_DEADPARENT;
	}

	proc_list_unlock();

#if CONFIG_FINE_LOCK_GROUPS
	lck_mtx_destroy(&child->p_mlock, proc_mlock_grp);
	lck_mtx_destroy(&child->p_ucred_mlock, proc_ucred_mlock_grp);
	lck_mtx_destroy(&child->p_fdmlock, proc_fdmlock_grp);
#if CONFIG_DTRACE
	lck_mtx_destroy(&child->p_dtrace_sprlock, proc_lck_grp);
#endif
	lck_spin_destroy(&child->p_slock, proc_slock_grp);
#else /* CONFIG_FINE_LOCK_GROUPS */
	lck_mtx_destroy(&child->p_mlock, proc_lck_grp);
	lck_mtx_destroy(&child->p_ucred_mlock, proc_lck_grp);
	lck_mtx_destroy(&child->p_fdmlock, proc_lck_grp);
#if CONFIG_DTRACE
	lck_mtx_destroy(&child->p_dtrace_sprlock, proc_lck_grp);
#endif
	lck_spin_destroy(&child->p_slock, proc_lck_grp);
#endif /* CONFIG_FINE_LOCK_GROUPS */

	FREE_ZONE(child, sizeof *child, M_PROC);
	if ((locked == 1) && (droplock == 0))
		proc_list_lock();

	return (1);
}