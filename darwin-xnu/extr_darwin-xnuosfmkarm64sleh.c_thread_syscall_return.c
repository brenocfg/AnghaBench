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
typedef  int /*<<< orphan*/  thread_t ;
struct arm_saved_state {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_2__ {int /*<<< orphan*/ * x; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int get_saved_state_svc_number (struct arm_saved_state*) ; 
 struct arm_saved_state* get_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_saved_state64 (struct arm_saved_state*) ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  mach_syscall_trace_exit (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* saved_state64 (struct arm_saved_state*) ; 
 int /*<<< orphan*/  thread_exception_return () ; 

__attribute__((noreturn))
void
thread_syscall_return(kern_return_t error)
{
	thread_t thread;
	struct arm_saved_state *state;

	thread = current_thread();
	state = get_user_regs(thread);

	assert(is_saved_state64(state));
	saved_state64(state)->x[0] = error;

#if DEBUG || DEVELOPMENT
	kern_allocation_name_t
	prior __assert_only = thread_get_kernel_state(thread)->allocation_name;
	assertf(prior == NULL, "thread_set_allocation_name(\"%s\") not cleared", kern_allocation_get_name(prior));
#endif /* DEBUG || DEVELOPMENT */

	if (kdebug_enable) {
		/* Invert syscall number (negative for a mach syscall) */
		mach_syscall_trace_exit(error, (-1) * get_saved_state_svc_number(state));
	}

	thread_exception_return();
}