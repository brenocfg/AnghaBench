#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__* r; } ;
typedef  TYPE_2__ x86_saved_state_t ;
typedef  TYPE_3__* uthread_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  syscall_arg_t ;
struct mach_call_args {int dummy; } ;
struct TYPE_21__ {int /*<<< orphan*/  p_lock; } ;
typedef  TYPE_4__ proc_t ;
struct TYPE_22__ {int /*<<< orphan*/  stsy_return; scalar_t__* stsy_underlying; int /*<<< orphan*/  stsy_entry; } ;
typedef  TYPE_5__ machtrace_sysent_t ;
typedef  scalar_t__ (* mach_call_t ) (struct mach_call_args*) ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
typedef  TYPE_2__ arm_saved_state_t ;
struct TYPE_24__ {int rax; scalar_t__* x; } ;
struct TYPE_23__ {scalar_t__ t_dtrace_stop; TYPE_1__* t_lwp; } ;
struct TYPE_20__ {void* t_dtrace_syscall_args; } ;
struct TYPE_18__ {int /*<<< orphan*/  lwp_nostop; } ;
struct TYPE_17__ {int eax; scalar_t__* r; } ;

/* Variables and functions */
 size_t ARM64_SYSCALL_CODE_REG_NUM ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_IDNONE ; 
 int /*<<< orphan*/  PR_REQUESTED ; 
 int SYSCALL_NUMBER_MASK ; 
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_8__* curthread ; 
 scalar_t__ find_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ is_saved_state32 (TYPE_2__*) ; 
 scalar_t__ is_saved_state64 (TYPE_2__*) ; 
 int /*<<< orphan*/  machtrace_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* machtrace_sysent ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__* saved_state32 (TYPE_2__*) ; 
 TYPE_9__* saved_state64 (TYPE_2__*) ; 
 int /*<<< orphan*/  stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ttoproc (TYPE_8__*) ; 

__attribute__((used)) static kern_return_t
dtrace_machtrace_syscall(struct mach_call_args *args)
{
	int code;	/* The mach call number */

	machtrace_sysent_t *sy;
	dtrace_id_t id;
	kern_return_t rval;
#if 0 /* XXX */
	proc_t *p;
#endif
	syscall_arg_t *ip = (syscall_arg_t *)args;
	mach_call_t mach_call;

#if defined (__x86_64__)
	{
		pal_register_cache_state(current_thread(), VALID);
		x86_saved_state_t   *tagged_regs = (x86_saved_state_t *)find_user_regs(current_thread());

		if (is_saved_state64(tagged_regs)) {
			code = saved_state64(tagged_regs)->rax & SYSCALL_NUMBER_MASK;
		} else {
			code = -saved_state32(tagged_regs)->eax;
		}
	}
#elif defined(__arm__)
	{
		/* r12 has the machcall number, but it is -ve */
		arm_saved_state_t *arm_regs = (arm_saved_state_t *) find_user_regs(current_thread());
		code = (int)arm_regs->r[12];
		ASSERT(code < 0);    /* Otherwise it would be a Unix syscall */
		code = -code;
	}
#elif defined(__arm64__)
	{
		/* From arm/thread_status.h:get_saved_state_svc_number */
		arm_saved_state_t *arm_regs = (arm_saved_state_t *) find_user_regs(current_thread());
		if (is_saved_state32(arm_regs)) {
			code = (int)saved_state32(arm_regs)->r[12];
		} else {
			code = (int)saved_state64(arm_regs)->x[ARM64_SYSCALL_CODE_REG_NUM];
		}

                /* From bsd/arm64.c:mach_syscall */
		ASSERT(code < 0);    /* Otherwise it would be a Unix syscall */
		code = -code;		
	}
#else
#error Unknown Architecture
#endif

	sy = &machtrace_sysent[code];

	if ((id = sy->stsy_entry) != DTRACE_IDNONE) {
		uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());	

		if (uthread)
			uthread->t_dtrace_syscall_args = (void *)ip;
		
		(*machtrace_probe)(id, *ip, *(ip+1), *(ip+2), *(ip+3), *(ip+4));
		
		if (uthread)
			uthread->t_dtrace_syscall_args = (void *)0;		
	}

#if 0 /* XXX */
	/*
	 * APPLE NOTE:  Not implemented.
	 * We want to explicitly allow DTrace consumers to stop a process
	 * before it actually executes the meat of the syscall.
	 */
	p = ttoproc(curthread);
	mutex_enter(&p->p_lock);
	if (curthread->t_dtrace_stop && !curthread->t_lwp->lwp_nostop) {
		curthread->t_dtrace_stop = 0;
		stop(PR_REQUESTED, 0);
	}
	mutex_exit(&p->p_lock);
#endif

	mach_call = (mach_call_t)(*sy->stsy_underlying);
	rval = mach_call(args);

	if ((id = sy->stsy_return) != DTRACE_IDNONE)
		(*machtrace_probe)(id, (uint64_t)rval, 0, 0, 0, 0);

	return (rval);
}