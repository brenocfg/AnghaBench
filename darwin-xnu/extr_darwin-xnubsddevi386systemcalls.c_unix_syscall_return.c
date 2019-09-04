#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rflags; } ;
struct TYPE_7__ {int rax; int rdx; TYPE_1__ isf; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
struct TYPE_8__ {int eax; int edx; int /*<<< orphan*/  efl; } ;
typedef  TYPE_3__ x86_saved_state32_t ;
typedef  int uint64_t ;
typedef  void* u_int ;
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {unsigned int syscall_code; int* uu_rval; scalar_t__ uu_lowpri_window; int /*<<< orphan*/  uu_flag; } ;
struct sysent {int sy_return_type; } ;
struct proc {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SYSCALL_EXIT (unsigned int,struct proc*,struct uthread*,int) ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DBG_BSD_EXCP_SC ; 
 int DBG_FUNC_END ; 
 int /*<<< orphan*/  DEBUG_KPRINT_SYSCALL_UNIX (char*,int,int,int) ; 
 int /*<<< orphan*/  DIRTY ; 
 int /*<<< orphan*/  EFL_CF ; 
 int EJUSTRETURN ; 
 int ERESTART ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SYS_invalid ; 
 int /*<<< orphan*/  UT_NOTCANCELPT ; 
#define  _SYSCALL_RET_ADDR_T 135 
#define  _SYSCALL_RET_INT_T 134 
#define  _SYSCALL_RET_NONE 133 
#define  _SYSCALL_RET_OFF_T 132 
#define  _SYSCALL_RET_SIZE_T 131 
#define  _SYSCALL_RET_SSIZE_T 130 
#define  _SYSCALL_RET_UINT64_T 129 
#define  _SYSCALL_RET_UINT_T 128 
 int /*<<< orphan*/  code_is_kdebug_trace (unsigned int) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  find_user_regs (int /*<<< orphan*/ ) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 unsigned int nsysent ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pal_syscall_restart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ proc_is64bit (struct proc*) ; 
 TYPE_3__* saved_state32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* saved_state64 (int /*<<< orphan*/ ) ; 
 struct sysent* sysent ; 
 int /*<<< orphan*/  thread_exception_return () ; 
 int /*<<< orphan*/  throttle_lowpri_io (int) ; 

void
unix_syscall_return(int error)
{
	thread_t		thread;
	struct uthread		*uthread;
	struct proc *p;
	unsigned int code;
	struct sysent *callp;

	thread = current_thread();
	uthread = get_bsdthread_info(thread);

	pal_register_cache_state(thread, DIRTY);

	p = current_proc();

	if (proc_is64bit(p)) {
		x86_saved_state64_t *regs;

		regs = saved_state64(find_user_regs(thread));

		code = uthread->syscall_code;
		callp = (code >= nsysent) ? &sysent[SYS_invalid] : &sysent[code];

#if CONFIG_DTRACE
		if (callp->sy_call == dtrace_systrace_syscall)
			dtrace_systrace_syscall_return( code, error, uthread->uu_rval );
#endif /* CONFIG_DTRACE */
		AUDIT_SYSCALL_EXIT(code, p, uthread, error);

		if (error == ERESTART) {
			/*
			 * repeat the syscall
			 */
			pal_syscall_restart( thread, find_user_regs(thread) );
		}
		else if (error != EJUSTRETURN) {
			if (error) {
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
			"unix_syscall_return: error=%d retval=(%llu,%llu)\n",
			error, regs->rax, regs->rdx);
	} else {
		x86_saved_state32_t	*regs;

		regs = saved_state32(find_user_regs(thread));

		regs->efl &= ~(EFL_CF);

		code = uthread->syscall_code;
		callp = (code >= nsysent) ? &sysent[SYS_invalid] : &sysent[code];

#if CONFIG_DTRACE
		if (callp->sy_call == dtrace_systrace_syscall)
			dtrace_systrace_syscall_return( code, error, uthread->uu_rval );
#endif /* CONFIG_DTRACE */
		AUDIT_SYSCALL_EXIT(code, p, uthread, error);

		if (error == ERESTART) {
			pal_syscall_restart( thread, find_user_regs(thread) );
		}
		else if (error != EJUSTRETURN) {
			if (error) {
				regs->eax = error;
				regs->efl |= EFL_CF;	/* carry bit */
			} else { /* (not error) */
				regs->eax = uthread->uu_rval[0];
				regs->edx = uthread->uu_rval[1];
			} 
		}
		DEBUG_KPRINT_SYSCALL_UNIX(
			"unix_syscall_return: error=%d retval=(%u,%u)\n",
			error, regs->eax, regs->edx);
	}


	uthread->uu_flag &= ~UT_NOTCANCELPT;

#if DEBUG || DEVELOPMENT
	kern_allocation_name_t
	prior __assert_only = thread_set_allocation_name(NULL);
	assertf(prior == NULL, "thread_set_allocation_name(\"%s\") not cleared", kern_allocation_get_name(prior));
#endif /* DEBUG || DEVELOPMENT */

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
	if (!code_is_kdebug_trace(code))
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
			BSDDBG_CODE(DBG_BSD_EXCP_SC, code) | DBG_FUNC_END,
			error, uthread->uu_rval[0], uthread->uu_rval[1], p->p_pid, 0);

	thread_exception_return();
	/* NOTREACHED */
}