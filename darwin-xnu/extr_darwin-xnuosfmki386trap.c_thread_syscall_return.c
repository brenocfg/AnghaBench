#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rax; } ;
typedef  TYPE_1__ x86_saved_state64_t ;
struct TYPE_6__ {void* eax; } ;
typedef  TYPE_2__ x86_saved_state32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  void* kern_return_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int /*<<< orphan*/  DBG_MACH_EXCP_SC ; 
 int /*<<< orphan*/  DIRTY ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int SYSCALL_CLASS_MACH ; 
 int SYSCALL_CLASS_MASK ; 
 int SYSCALL_CLASS_SHIFT ; 
 int SYSCALL_NUMBER_MASK ; 
 TYPE_2__* USER_REGS32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* USER_REGS64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_exception_return () ; 
 scalar_t__ thread_is_64bit_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throttle_lowpri_io (int) ; 

__attribute__((noreturn))
void
thread_syscall_return(
        kern_return_t ret)
{
        thread_t	thr_act = current_thread();
	boolean_t	is_mach;
	int		code;

	pal_register_cache_state(thr_act, DIRTY);

        if (thread_is_64bit_addr(thr_act)) {
	        x86_saved_state64_t	*regs;
		
		regs = USER_REGS64(thr_act);

		code = (int) (regs->rax & SYSCALL_NUMBER_MASK);
		is_mach = (regs->rax & SYSCALL_CLASS_MASK)
			    == (SYSCALL_CLASS_MACH << SYSCALL_CLASS_SHIFT);
		if (kdebug_enable && is_mach) {
		        /* Mach trap */
		        KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
			      MACHDBG_CODE(DBG_MACH_EXCP_SC,code)|DBG_FUNC_END,
			      ret, 0, 0, 0, 0);
		}
		regs->rax = ret;
#if DEBUG
		if (is_mach)
			DEBUG_KPRINT_SYSCALL_MACH(
				"thread_syscall_return: 64-bit mach ret=%u\n",
				ret);
		else
			DEBUG_KPRINT_SYSCALL_UNIX(
				"thread_syscall_return: 64-bit unix ret=%u\n",
				ret);
#endif
	} else {
	        x86_saved_state32_t	*regs;
		
		regs = USER_REGS32(thr_act);

		code = ((int) regs->eax);
		is_mach = (code < 0);
		if (kdebug_enable && is_mach) {
		        /* Mach trap */
		        KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
			      MACHDBG_CODE(DBG_MACH_EXCP_SC,-code)|DBG_FUNC_END,
			      ret, 0, 0, 0, 0);
		}
		regs->eax = ret;
#if DEBUG
		if (is_mach)
			DEBUG_KPRINT_SYSCALL_MACH(
				"thread_syscall_return: 32-bit mach ret=%u\n",
				ret);
		else
			DEBUG_KPRINT_SYSCALL_UNIX(
				"thread_syscall_return: 32-bit unix ret=%u\n",
				ret);
#endif
	}

#if DEBUG || DEVELOPMENT
	kern_allocation_name_t
	prior __assert_only = thread_get_kernel_state(thr_act)->allocation_name;
	assertf(prior == NULL, "thread_set_allocation_name(\"%s\") not cleared", kern_allocation_get_name(prior));
#endif /* DEBUG || DEVELOPMENT */

	throttle_lowpri_io(1);

	thread_exception_return();
        /*NOTREACHED*/
}