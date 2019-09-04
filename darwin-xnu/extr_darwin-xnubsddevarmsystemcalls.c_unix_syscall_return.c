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
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {unsigned short syscall_code; int /*<<< orphan*/ * uu_rval; scalar_t__ uu_lowpri_window; int /*<<< orphan*/  uu_flag; } ;
struct sysent {int dummy; } ;
struct proc {int /*<<< orphan*/  p_pid; } ;
struct arm_saved_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SYSCALL_EXIT (unsigned short,struct proc*,struct uthread*,int) ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  DBG_BSD_EXCP_SC ; 
 int DBG_FUNC_END ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SYS_invalid ; 
 int /*<<< orphan*/  UT_NOTCANCELPT ; 
 int /*<<< orphan*/  arm_prepare_syscall_return (struct sysent*,struct arm_saved_state*,struct uthread*,int) ; 
 int /*<<< orphan*/  code_is_kdebug_trace (unsigned short) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 struct arm_saved_state* find_user_regs (int /*<<< orphan*/ ) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ kdebug_enable ; 
 unsigned short nsysent ; 
 struct sysent* sysent ; 
 int /*<<< orphan*/  thread_exception_return () ; 
 int /*<<< orphan*/  throttle_lowpri_io (int) ; 

void
unix_syscall_return(int error)
{
	thread_t        thread_act;
	struct uthread *uthread;
	struct proc    *proc;
	struct arm_saved_state *regs;
	unsigned short  code;
	struct sysent  *callp;

#define unix_syscall_return_kprintf(x...)	/* kprintf("unix_syscall_retur
						 * n: " x) */

	thread_act = current_thread();
	proc = current_proc();
	uthread = get_bsdthread_info(thread_act);

	regs = find_user_regs(thread_act);
	code = uthread->syscall_code;
	callp = (code >= nsysent) ? &sysent[SYS_invalid] : &sysent[code];

#if CONFIG_DTRACE
	if (callp->sy_call == dtrace_systrace_syscall)
		dtrace_systrace_syscall_return( code, error, uthread->uu_rval );
#endif /* CONFIG_DTRACE */
#if DEBUG || DEVELOPMENT
	kern_allocation_name_t
	prior __assert_only = thread_set_allocation_name(NULL);
	assertf(prior == NULL, "thread_set_allocation_name(\"%s\") not cleared", kern_allocation_get_name(prior));
#endif /* DEBUG || DEVELOPMENT */

	AUDIT_SYSCALL_EXIT(code, proc, uthread, error);

	/*
	 * Get index into sysent table
	 */
	arm_prepare_syscall_return(callp, regs, uthread, error);

	uthread->uu_flag &= ~UT_NOTCANCELPT;

	if (uthread->uu_lowpri_window) {
		/*
		 * task is marked as a low priority I/O type
		 * and the I/O we issued while in this system call
		 * collided with normal I/O operations... we'll
		 * delay in order to mitigate the impact of this
		 * task on the normal operation of the system
		 */
		throttle_lowpri_io(1);
	}
#if (KDEBUG_LEVEL >= KDEBUG_LEVEL_IST)
	if (kdebug_enable && !code_is_kdebug_trace(code)) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			BSDDBG_CODE(DBG_BSD_EXCP_SC, code) | DBG_FUNC_END,
			error, uthread->uu_rval[0], uthread->uu_rval[1], proc->p_pid, 0);
	}
#endif

	thread_exception_return();
	/* NOTREACHED */
}