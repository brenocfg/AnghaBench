#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_5__ {int eax; int /*<<< orphan*/  uesp; } ;
typedef  TYPE_1__ x86_saved_state32_t ;
struct uthread {int dummy; } ;
struct mach_call_args {void* arg1; int /*<<< orphan*/  arg4; int /*<<< orphan*/  arg3; int /*<<< orphan*/  arg2; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  void* (* mach_call_t ) (struct mach_call_args*) ;
typedef  void* kern_return_t ;
struct TYPE_6__ {int mach_trap_arg_count; scalar_t__ mach_trap_function; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_EXCP_SC ; 
 int /*<<< orphan*/  DEBUG_KPRINT_SYSCALL_MACH (char*,void*,...) ; 
 int /*<<< orphan*/  EXC_SYSCALL ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* KERN_SUCCESS ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i386_exception (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  is_saved_state32 (int /*<<< orphan*/ *) ; 
 scalar_t__ kern_invalid ; 
 void* mach_call_arg_munger32 (int /*<<< orphan*/ ,struct mach_call_args*,TYPE_3__*) ; 
 int /*<<< orphan*/ * mach_syscall_name_table ; 
 int mach_trap_count ; 
 TYPE_3__* mach_trap_table ; 
 TYPE_1__* saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exception_return () ; 
 int /*<<< orphan*/  throttle_lowpri_io (int) ; 
 int /*<<< orphan*/  uthread_reset_proc_refcount (struct uthread*) ; 

__attribute__((noreturn))
void
mach_call_munger(x86_saved_state_t *state)
{
	int argc;
	int call_number;
	mach_call_t mach_call;
	kern_return_t retval;
	struct mach_call_args args = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	x86_saved_state32_t	*regs;

	struct uthread *ut = get_bsdthread_info(current_thread());
	uthread_reset_proc_refcount(ut);

	assert(is_saved_state32(state));
	regs = saved_state32(state);

	call_number = -(regs->eax);

	DEBUG_KPRINT_SYSCALL_MACH(
		"mach_call_munger: code=%d(%s)\n",
		call_number, mach_syscall_name_table[call_number]);
#if DEBUG_TRACE
	kprintf("mach_call_munger(0x%08x) code=%d\n", regs, call_number);
#endif

	if (call_number < 0 || call_number >= mach_trap_count) {
		i386_exception(EXC_SYSCALL, call_number, 1);
		/* NOTREACHED */
	}
	mach_call = (mach_call_t)mach_trap_table[call_number].mach_trap_function;

	if (mach_call == (mach_call_t)kern_invalid) {
		DEBUG_KPRINT_SYSCALL_MACH(
			"mach_call_munger: kern_invalid 0x%x\n", regs->eax);
		i386_exception(EXC_SYSCALL, call_number, 1);
		/* NOTREACHED */
	}

	argc = mach_trap_table[call_number].mach_trap_arg_count;
	if (argc) {
		retval = mach_call_arg_munger32(regs->uesp, &args,  &mach_trap_table[call_number]);
		if (retval != KERN_SUCCESS) {
			regs->eax = retval;

			DEBUG_KPRINT_SYSCALL_MACH(
				"mach_call_munger: retval=0x%x\n", retval);

			thread_exception_return();
			/* NOTREACHED */
		}
	}

#ifdef MACH_BSD
	mach_kauth_cred_uthread_update();
#endif

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		MACHDBG_CODE(DBG_MACH_EXCP_SC, (call_number)) | DBG_FUNC_START,
		args.arg1, args.arg2, args.arg3, args.arg4, 0);

	retval = mach_call(&args);

	DEBUG_KPRINT_SYSCALL_MACH("mach_call_munger: retval=0x%x\n", retval);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		MACHDBG_CODE(DBG_MACH_EXCP_SC,(call_number)) | DBG_FUNC_END,
		retval, 0, 0, 0, 0);

	regs->eax = retval;

#if DEBUG || DEVELOPMENT
	kern_allocation_name_t
	prior __assert_only = thread_get_kernel_state(current_thread())->allocation_name;
	assertf(prior == NULL, "thread_set_allocation_name(\"%s\") not cleared", kern_allocation_get_name(prior));
#endif /* DEBUG || DEVELOPMENT */

	throttle_lowpri_io(1);

#if PROC_REF_DEBUG
	if (__improbable(uthread_get_proc_refcount(ut) != 0)) {
		panic("system call returned with uu_proc_refcount != 0");
	}
#endif

	thread_exception_return();
	/* NOTREACHED */
}