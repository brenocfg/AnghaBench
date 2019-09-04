#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_4__ {int rip; int /*<<< orphan*/  rflags; scalar_t__ rsp; } ;
struct TYPE_5__ {unsigned int rax; unsigned int rdi; unsigned int rsi; int rdx; TYPE_1__ isf; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint64_t ;
typedef  void* u_int ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  syscall_arg_t ;
struct uthread {int uu_flag; int* uu_rval; unsigned int syscall_code; int uu_lowpri_window; int /*<<< orphan*/ * uu_arg; } ;
struct sysent {int sy_narg; int (* sy_call ) (void*,void*,int*) ;int sy_return_type; } ;
struct proc {int dummy; } ;
typedef  int pid_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SYSCALL_ENTER (unsigned int,struct proc*,struct uthread*) ; 
 int /*<<< orphan*/  AUDIT_SYSCALL_EXIT (unsigned int,struct proc*,struct uthread*,int) ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DBG_BSD_EXCP_SC ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DEBUG_KPRINT_SYSCALL_UNIX (char*,int,int,int) ; 
 int /*<<< orphan*/  EFL_CF ; 
 int EJUSTRETURN ; 
 unsigned int EPERM ; 
 int ERESTART ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 unsigned int SYSCALL_NUMBER_MASK ; 
 unsigned int SYS_invalid ; 
 scalar_t__ TRUE ; 
 int UT_NOTCANCELPT ; 
 int UT_VFORK ; 
#define  _SYSCALL_RET_ADDR_T 135 
#define  _SYSCALL_RET_INT_T 134 
#define  _SYSCALL_RET_NONE 133 
#define  _SYSCALL_RET_OFF_T 132 
#define  _SYSCALL_RET_SIZE_T 131 
#define  _SYSCALL_RET_SSIZE_T 130 
#define  _SYSCALL_RET_UINT64_T 129 
#define  _SYSCALL_RET_UINT_T 128 
 scalar_t__ __improbable (int) ; 
 scalar_t__ __probable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  code_is_kdebug_trace (unsigned int) ; 
 int copyin (int /*<<< orphan*/ ,char*,int) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdtask_info (int /*<<< orphan*/ ) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int is_saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kauth_cred_uthread_update (struct uthread*,struct proc*) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned int*,int) ; 
 unsigned int nsysent ; 
 int /*<<< orphan*/  pal_syscall_restart (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int proc_pid (struct proc*) ; 
 TYPE_2__* saved_state64 (int /*<<< orphan*/ *) ; 
 int stub1 (void*,void*,int*) ; 
 int* syscallnames ; 
 struct sysent* sysent ; 
 int /*<<< orphan*/  task_terminate_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_exception_return () ; 
 int /*<<< orphan*/  throttle_lowpri_io (int) ; 
 int /*<<< orphan*/  uthread_reset_proc_refcount (struct uthread*) ; 

__attribute__((noreturn))
void
unix_syscall64(x86_saved_state_t *state)
{
	thread_t	thread;
	void			*vt;
	unsigned int	code;
	struct sysent	*callp;
	int		args_in_regs;
	boolean_t	args_start_at_rdi;
	int		error;
	struct proc	*p;
	struct uthread	*uthread;
	x86_saved_state64_t *regs;
	pid_t		pid;

	assert(is_saved_state64(state));
	regs = saved_state64(state);
#if	DEBUG
	if (regs->rax == 0x2000800)
		thread_exception_return();
#endif
	thread = current_thread();
	uthread = get_bsdthread_info(thread);

	uthread_reset_proc_refcount(uthread);

	/* Get the approriate proc; may be different from task's for vfork() */
	if (__probable(!(uthread->uu_flag & UT_VFORK)))
		p = (struct proc *)get_bsdtask_info(current_task());
	else 
		p = current_proc();

	/* Verify that we are not being called from a task without a proc */
	if (__improbable(p == NULL)) {
		regs->rax = EPERM;
		regs->isf.rflags |= EFL_CF;
		task_terminate_internal(current_task());
		thread_exception_return();
		/* NOTREACHED */
	}

	code = regs->rax & SYSCALL_NUMBER_MASK;
	DEBUG_KPRINT_SYSCALL_UNIX(
		"unix_syscall64: code=%d(%s) rip=%llx\n",
		code, syscallnames[code >= nsysent ? SYS_invalid : code], regs->isf.rip);
	callp = (code >= nsysent) ? &sysent[SYS_invalid] : &sysent[code];

	vt = (void *)uthread->uu_arg;

	if (__improbable(callp == sysent)) {
	        /*
		 * indirect system call... system call number
		 * passed as 'arg0'
		 */
		code = regs->rdi;
		callp = (code >= nsysent) ? &sysent[SYS_invalid] : &sysent[code];
		args_start_at_rdi = FALSE;
		args_in_regs = 5;
	} else {
		args_start_at_rdi = TRUE;
		args_in_regs = 6;
	}

	if (callp->sy_narg != 0) {
		assert(callp->sy_narg <= 8); /* size of uu_arg */

		args_in_regs = MIN(args_in_regs, callp->sy_narg);
		memcpy(vt, args_start_at_rdi ? &regs->rdi : &regs->rsi, args_in_regs * sizeof(syscall_arg_t));


		if (!code_is_kdebug_trace(code)) {
			uint64_t *ip = (uint64_t *)vt;

			KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
				BSDDBG_CODE(DBG_BSD_EXCP_SC, code) | DBG_FUNC_START,
				(int)(*ip), (int)(*(ip+1)), (int)(*(ip+2)), (int)(*(ip+3)), 0);
		}

		if (__improbable(callp->sy_narg > args_in_regs)) {
			int copyin_count;

			copyin_count = (callp->sy_narg - args_in_regs) * sizeof(syscall_arg_t);

			error = copyin((user_addr_t)(regs->isf.rsp + sizeof(user_addr_t)), (char *)&uthread->uu_arg[args_in_regs], copyin_count);
			if (error) {
				regs->rax = error;
				regs->isf.rflags |= EFL_CF;
				thread_exception_return();
				/* NOTREACHED */
			}
		}
	} else
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			BSDDBG_CODE(DBG_BSD_EXCP_SC, code) | DBG_FUNC_START,
			0, 0, 0, 0, 0);

	/*
	 * Delayed binding of thread credential to process credential, if we
	 * are not running with an explicitly set thread credential.
	 */
	kauth_cred_uthread_update(uthread, p);

	uthread->uu_rval[0] = 0;
	uthread->uu_rval[1] = 0;
	uthread->uu_flag |= UT_NOTCANCELPT;
	uthread->syscall_code = code;
	pid = proc_pid(p);

#ifdef JOE_DEBUG
        uthread->uu_iocount = 0;
        uthread->uu_vpindex = 0;
#endif

	AUDIT_SYSCALL_ENTER(code, p, uthread);
	error = (*(callp->sy_call))((void *) p, vt, &(uthread->uu_rval[0]));
	AUDIT_SYSCALL_EXIT(code, p, uthread, error);

#ifdef JOE_DEBUG
        if (uthread->uu_iocount)
               printf("system call returned with uu_iocount != 0\n");
#endif

#if CONFIG_DTRACE
	uthread->t_dtrace_errno = error;
#endif /* CONFIG_DTRACE */
	
	if (__improbable(error == ERESTART)) {
		/*
		 * all system calls come through via the syscall instruction
		 * in 64 bit mode... its 2 bytes in length
		 * move the user's pc back to repeat the syscall:
		 */
		pal_syscall_restart( thread, state );
	}
	else if (error != EJUSTRETURN) {
		if (__improbable(error)) {
			regs->rax = error;
			regs->isf.rflags |= EFL_CF;	/* carry bit */
		} else { /* (not error) */

			switch (callp->sy_return_type) {
			case _SYSCALL_RET_INT_T:
				regs->rax = uthread->uu_rval[0];
				regs->rdx = uthread->uu_rval[1];
				break;
			case _SYSCALL_RET_UINT_T:
				regs->rax = ((u_int)uthread->uu_rval[0]);
				regs->rdx = ((u_int)uthread->uu_rval[1]);
				break;
			case _SYSCALL_RET_OFF_T:
			case _SYSCALL_RET_ADDR_T:
			case _SYSCALL_RET_SIZE_T:
			case _SYSCALL_RET_SSIZE_T:
			case _SYSCALL_RET_UINT64_T:
			        regs->rax = *((uint64_t *)(&uthread->uu_rval[0]));
				regs->rdx = 0;
				break;
			case _SYSCALL_RET_NONE:
				break;
			default:
				panic("unix_syscall: unknown return type");
				break;
			}
			regs->isf.rflags &= ~EFL_CF;
		} 
	}

	DEBUG_KPRINT_SYSCALL_UNIX(
		"unix_syscall64: error=%d retval=(%llu,%llu)\n",
		error, regs->rax, regs->rdx);
	
	uthread->uu_flag &= ~UT_NOTCANCELPT;

#if DEBUG || DEVELOPMENT
	kern_allocation_name_t
	prior __assert_only = thread_set_allocation_name(NULL);
	assertf(prior == NULL, "thread_set_allocation_name(\"%s\") not cleared", kern_allocation_get_name(prior));
#endif /* DEBUG || DEVELOPMENT */

	if (__improbable(uthread->uu_lowpri_window)) {
	        /*
		 * task is marked as a low priority I/O type
		 * and the I/O we issued while in this system call
		 * collided with normal I/O operations... we'll
		 * delay in order to mitigate the impact of this
		 * task on the normal operation of the system
		 */
		throttle_lowpri_io(1);
	}
	if (__probable(!code_is_kdebug_trace(code)))
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
			BSDDBG_CODE(DBG_BSD_EXCP_SC, code) | DBG_FUNC_END,
			error, uthread->uu_rval[0], uthread->uu_rval[1], pid, 0);

#if PROC_REF_DEBUG
	if (__improbable(uthread_get_proc_refcount(uthread))) {
		panic("system call returned with uu_proc_refcount != 0");
	}
#endif

	thread_exception_return();
	/* NOTREACHED */
}