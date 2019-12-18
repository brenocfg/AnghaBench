#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* uthread_t ;
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/ * thread_t ;
typedef  scalar_t__ rlim_t ;
typedef  TYPE_3__* proc_t ;
typedef  int /*<<< orphan*/  coalition_t ;
struct TYPE_19__ {int p_pid; char* p_comm; void* p_acflag; int /*<<< orphan*/  p_ucred; int /*<<< orphan*/  task; int /*<<< orphan*/  p_lflag; int /*<<< orphan*/  p_stat; int /*<<< orphan*/ * p_vforkact; TYPE_1__* p_rlimit; } ;
struct TYPE_18__ {int uu_flag; int /*<<< orphan*/  uu_sigmask; int /*<<< orphan*/  uu_vforkmask; void* uu_userstate; TYPE_3__* uu_proc; } ;
struct TYPE_17__ {scalar_t__ rlim_cur; } ;

/* Variables and functions */
 void* AFORK ; 
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
#define  PROC_CREATE_FORK 130 
#define  PROC_CREATE_SPAWN 129 
#define  PROC_CREATE_VFORK 128 
 int /*<<< orphan*/  P_LINVFORK ; 
 int /*<<< orphan*/  P_LPPWAIT ; 
 size_t RLIMIT_NPROC ; 
 int /*<<< orphan*/  SRUN ; 
 int /*<<< orphan*/  TRUE ; 
 int UT_SETUID ; 
 int UT_VFORK ; 
 int UT_VFORKING ; 
 int UT_WASSETUID ; 
 scalar_t__ act_thread_csave () ; 
 int chgproccnt (scalar_t__,int) ; 
 int /*<<< orphan*/ * cloneproc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  dtrace_proc_fork (TYPE_3__*,TYPE_3__*,int) ; 
 TYPE_3__* forkproc (TYPE_3__*) ; 
 int /*<<< orphan*/  get_bsdtask_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ *) ; 
 scalar_t__ kauth_getruid () ; 
 int /*<<< orphan*/  mac_cred_label_associate_fork (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int mac_proc_check_fork (TYPE_3__*) ; 
 int maxproc ; 
 int nprocs ; 
 int /*<<< orphan*/  panic (char*,int,...) ; 
 int /*<<< orphan*/  pid ; 
 int /*<<< orphan*/  pinsertchild (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  proc_vfork_begin (TYPE_3__*) ; 
 int /*<<< orphan*/  proc_vfork_end (TYPE_3__*) ; 
 int /*<<< orphan*/  set_security_token (TYPE_3__*) ; 
 int /*<<< orphan*/  tablefull (char*) ; 
 int /*<<< orphan*/  task_bank_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_set_child (int /*<<< orphan*/ *,int) ; 

int
fork1(proc_t parent_proc, thread_t *child_threadp, int kind, coalition_t *coalitions)
{
	thread_t parent_thread = (thread_t)current_thread();
	uthread_t parent_uthread = (uthread_t)get_bsdthread_info(parent_thread);
	proc_t child_proc = NULL;	/* set in switch, but compiler... */
	thread_t child_thread = NULL;
	uid_t uid;
	int count;
	int err = 0;
	int spawn = 0;

	/*
	 * Although process entries are dynamically created, we still keep
	 * a global limit on the maximum number we will create.  Don't allow
	 * a nonprivileged user to use the last process; don't let root
	 * exceed the limit. The variable nprocs is the current number of
	 * processes, maxproc is the limit.
	 */
	uid = kauth_getruid();
	proc_list_lock();
	if ((nprocs >= maxproc - 1 && uid != 0) || nprocs >= maxproc) {
#if (DEVELOPMENT || DEBUG) && CONFIG_EMBEDDED
		/*
		 * On the development kernel, panic so that the fact that we hit
		 * the process limit is obvious, as this may very well wedge the
		 * system.
		 */
		panic("The process table is full; parent pid=%d", parent_proc->p_pid);
#endif
		proc_list_unlock();
		tablefull("proc");
		return (EAGAIN);
	}
	proc_list_unlock();

	/*
	 * Increment the count of procs running with this uid. Don't allow
	 * a nonprivileged user to exceed their current limit, which is
	 * always less than what an rlim_t can hold.
	 * (locking protection is provided by list lock held in chgproccnt)
	 */
	count = chgproccnt(uid, 1);
	if (uid != 0 &&
	    (rlim_t)count > parent_proc->p_rlimit[RLIMIT_NPROC].rlim_cur) {
#if (DEVELOPMENT || DEBUG) && CONFIG_EMBEDDED
		/*
		 * On the development kernel, panic so that the fact that we hit
		 * the per user process limit is obvious.  This may be less dire
		 * than hitting the global process limit, but we cannot rely on
		 * that.
		 */
		panic("The per-user process limit has been hit; parent pid=%d, uid=%d", parent_proc->p_pid, uid);
#endif
	    	err = EAGAIN;
		goto bad;
	}

#if CONFIG_MACF
	/*
	 * Determine if MAC policies applied to the process will allow
	 * it to fork.  This is an advisory-only check.
	 */
	err = mac_proc_check_fork(parent_proc);
	if (err  != 0) {
		goto bad;
	}
#endif

	switch(kind) {
	case PROC_CREATE_VFORK:
		/*
		 * Prevent a vfork while we are in vfork(); we should
		 * also likely preventing a fork here as well, and this
		 * check should then be outside the switch statement,
		 * since the proc struct contents will copy from the
		 * child and the tash/thread/uthread from the parent in
		 * that case.  We do not support vfork() in vfork()
		 * because we don't have to; the same non-requirement
		 * is true of both fork() and posix_spawn() and any
		 * call  other than execve() amd _exit(), but we've
		 * been historically lenient, so we continue to be so
		 * (for now).
		 *
		 * <rdar://6640521> Probably a source of random panics
		 */
		if (parent_uthread->uu_flag & UT_VFORK) {
			printf("fork1 called within vfork by %s\n", parent_proc->p_comm);
			err = EINVAL;
			goto bad;
		}

		/*
		 * Flag us in progress; if we chose to support vfork() in
		 * vfork(), we would chain our parent at this point (in
		 * effect, a stack push).  We don't, since we actually want
		 * to disallow everything not specified in the standard
		 */
		proc_vfork_begin(parent_proc);

		/* The newly created process comes with signal lock held */
		if ((child_proc = forkproc(parent_proc)) == NULL) {
			/* Failed to allocate new process */
			proc_vfork_end(parent_proc);
			err = ENOMEM;
			goto bad;
		}

// XXX BEGIN: wants to move to be common code (and safe)
#if CONFIG_MACF
		/*
		 * allow policies to associate the credential/label that
		 * we referenced from the parent ... with the child
		 * JMM - this really isn't safe, as we can drop that
		 *       association without informing the policy in other
		 *       situations (keep long enough to get policies changed)
		 */
		mac_cred_label_associate_fork(child_proc->p_ucred, child_proc);
#endif

		/*
		 * Propogate change of PID - may get new cred if auditing.
		 *
		 * NOTE: This has no effect in the vfork case, since
		 *	child_proc->task != current_task(), but we duplicate it
		 *	because this is probably, ultimately, wrong, since we
		 *	will be running in the "child" which is the parent task
		 *	with the wrong token until we get to the execve() or
		 *	_exit() call; a lot of "undefined" can happen before
		 *	that.
		 *
		 * <rdar://6640530> disallow everything but exeve()/_exit()?
		 */
		set_security_token(child_proc);

		AUDIT_ARG(pid, child_proc->p_pid);

// XXX END: wants to move to be common code (and safe)

		/*
		 * BORROW PARENT TASK, THREAD, UTHREAD FOR CHILD
		 *
		 * Note: this is where we would "push" state instead of setting
		 * it for nested vfork() support (see proc_vfork_end() for
		 * description if issues here).
		 */
		child_proc->task = parent_proc->task;

		child_proc->p_lflag  |= P_LINVFORK;
		child_proc->p_vforkact = parent_thread;
		child_proc->p_stat = SRUN;

		/*
		 * Until UT_VFORKING is cleared at the end of the vfork
		 * syscall, the process identity of this thread is slightly
		 * murky.
		 *
		 * As long as UT_VFORK and it's associated field (uu_proc)
		 * is set, current_proc() will always return the child process.
		 *
		 * However dtrace_proc_selfpid() returns the parent pid to
		 * ensure that e.g. the proc:::create probe actions accrue
		 * to the parent.  (Otherwise the child magically seems to
		 * have created itself!)
		 */
		parent_uthread->uu_flag |= UT_VFORK | UT_VFORKING;
		parent_uthread->uu_proc = child_proc;
		parent_uthread->uu_userstate = (void *)act_thread_csave();
		parent_uthread->uu_vforkmask = parent_uthread->uu_sigmask;

		/* temporarily drop thread-set-id state */
		if (parent_uthread->uu_flag & UT_SETUID) {
			parent_uthread->uu_flag |= UT_WASSETUID;
			parent_uthread->uu_flag &= ~UT_SETUID;
		}

		/* blow thread state information */
		/* XXX is this actually necessary, given syscall return? */
		thread_set_child(parent_thread, child_proc->p_pid);

		child_proc->p_acflag = AFORK;	/* forked but not exec'ed */

		/*
		 * Preserve synchronization semantics of vfork.  If
		 * waiting for child to exec or exit, set P_PPWAIT
		 * on child, and sleep on our proc (in case of exit).
		 */
		child_proc->p_lflag |= P_LPPWAIT;
		pinsertchild(parent_proc, child_proc);	/* set visible */

		break;

	case PROC_CREATE_SPAWN:
		/*
		 * A spawned process differs from a forked process in that
		 * the spawned process does not carry around the parents
		 * baggage with regard to address space copying, dtrace,
		 * and so on.
		 */
		spawn = 1;

		/* FALLSTHROUGH */

	case PROC_CREATE_FORK:
		/*
		 * When we clone the parent process, we are going to inherit
		 * its task attributes and memory, since when we fork, we
		 * will, in effect, create a duplicate of it, with only minor
		 * differences.  Contrarily, spawned processes do not inherit.
		 */
		if ((child_thread = cloneproc(parent_proc->task,
						spawn ? coalitions : NULL,
						parent_proc,
						spawn ? FALSE : TRUE,
						FALSE)) == NULL) {
			/* Failed to create thread */
			err = EAGAIN;
			goto bad;
		}

		/* copy current thread state into the child thread (only for fork) */
		if (!spawn) {
			thread_dup(child_thread);
		}

		/* child_proc = child_thread->task->proc; */
		child_proc = (proc_t)(get_bsdtask_info(get_threadtask(child_thread)));

// XXX BEGIN: wants to move to be common code (and safe)
#if CONFIG_MACF
		/*
		 * allow policies to associate the credential/label that
		 * we referenced from the parent ... with the child
		 * JMM - this really isn't safe, as we can drop that
		 *       association without informing the policy in other
		 *       situations (keep long enough to get policies changed)
		 */
		mac_cred_label_associate_fork(child_proc->p_ucred, child_proc);
#endif

		/*
		 * Propogate change of PID - may get new cred if auditing.
		 *
		 * NOTE: This has no effect in the vfork case, since
		 *	child_proc->task != current_task(), but we duplicate it
		 *	because this is probably, ultimately, wrong, since we
		 *	will be running in the "child" which is the parent task
		 *	with the wrong token until we get to the execve() or
		 *	_exit() call; a lot of "undefined" can happen before
		 *	that.
		 *
		 * <rdar://6640530> disallow everything but exeve()/_exit()?
		 */
		set_security_token(child_proc);

		AUDIT_ARG(pid, child_proc->p_pid);

// XXX END: wants to move to be common code (and safe)

		/*
		 * Blow thread state information; this is what gives the child
		 * process its "return" value from a fork() call.
		 *
		 * Note: this should probably move to fork() proper, since it
		 * is not relevent to spawn, and the value won't matter
		 * until we resume the child there.  If you are in here
		 * refactoring code, consider doing this at the same time.
		 */
		thread_set_child(child_thread, child_proc->p_pid);

		child_proc->p_acflag = AFORK;	/* forked but not exec'ed */

#if CONFIG_DTRACE
		dtrace_proc_fork(parent_proc, child_proc, spawn);
#endif	/* CONFIG_DTRACE */
		if (!spawn) {
			/*
			 * Of note, we need to initialize the bank context behind
			 * the protection of the proc_trans lock to prevent a race with exit.
			 */
			task_bank_init(get_threadtask(child_thread));
		}

		break;

	default:
		panic("fork1 called with unknown kind %d", kind);
		break;
	}


	/* return the thread pointer to the caller */
	*child_threadp = child_thread;

bad:
	/*
	 * In the error case, we return a 0 value for the returned pid (but
	 * it is ignored in the trampoline due to the error return); this
	 * is probably not necessary.
	 */
	if (err) {
		(void)chgproccnt(uid, -1);
	}

	return (err);
}