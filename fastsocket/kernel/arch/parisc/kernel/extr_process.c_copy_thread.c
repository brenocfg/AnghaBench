#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int* gr; unsigned long ksp; unsigned long kpc; unsigned long cr27; } ;
struct TYPE_2__ {struct pt_regs regs; } ;
struct task_struct {scalar_t__ personality; TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned long CLONE_SETTLS ; 
 scalar_t__ PER_HPUX ; 
 int THREAD_SIZE ; 
 unsigned long THREAD_SZ_ALGN ; 
 void* task_stack_page (struct task_struct*) ; 

int
copy_thread(unsigned long clone_flags, unsigned long usp,
	    unsigned long unused,	/* in ia64 this is "user_stack_size" */
	    struct task_struct * p, struct pt_regs * pregs)
{
	struct pt_regs * cregs = &(p->thread.regs);
	void *stack = task_stack_page(p);
	
	/* We have to use void * instead of a function pointer, because
	 * function pointers aren't a pointer to the function on 64-bit.
	 * Make them const so the compiler knows they live in .text */
	extern void * const ret_from_kernel_thread;
	extern void * const child_return;
#ifdef CONFIG_HPUX
	extern void * const hpux_child_return;
#endif

	*cregs = *pregs;

	/* Set the return value for the child.  Note that this is not
           actually restored by the syscall exit path, but we put it
           here for consistency in case of signals. */
	cregs->gr[28] = 0; /* child */

	/*
	 * We need to differentiate between a user fork and a
	 * kernel fork. We can't use user_mode, because the
	 * the syscall path doesn't save iaoq. Right now
	 * We rely on the fact that kernel_thread passes
	 * in zero for usp.
	 */
	if (usp == 1) {
		/* kernel thread */
		cregs->ksp = (unsigned long)stack + THREAD_SZ_ALGN;
		/* Must exit via ret_from_kernel_thread in order
		 * to call schedule_tail()
		 */
		cregs->kpc = (unsigned long) &ret_from_kernel_thread;
		/*
		 * Copy function and argument to be called from
		 * ret_from_kernel_thread.
		 */
#ifdef CONFIG_64BIT
		cregs->gr[27] = pregs->gr[27];
#endif
		cregs->gr[26] = pregs->gr[26];
		cregs->gr[25] = pregs->gr[25];
	} else {
		/* user thread */
		/*
		 * Note that the fork wrappers are responsible
		 * for setting gr[21].
		 */

		/* Use same stack depth as parent */
		cregs->ksp = (unsigned long)stack
			+ (pregs->gr[21] & (THREAD_SIZE - 1));
		cregs->gr[30] = usp;
		if (p->personality == PER_HPUX) {
#ifdef CONFIG_HPUX
			cregs->kpc = (unsigned long) &hpux_child_return;
#else
			BUG();
#endif
		} else {
			cregs->kpc = (unsigned long) &child_return;
		}
		/* Setup thread TLS area from the 4th parameter in clone */
		if (clone_flags & CLONE_SETTLS)
		  cregs->cr27 = pregs->gr[23];
	
	}

	return 0;
}