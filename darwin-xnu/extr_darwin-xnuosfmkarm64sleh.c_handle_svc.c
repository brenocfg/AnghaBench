#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct uthread {int dummy; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_5__ {scalar_t__ uthread; int /*<<< orphan*/  syscalls_unix; int /*<<< orphan*/  syscalls_mach; int /*<<< orphan*/  iotier_override; } ;

/* Variables and functions */
 scalar_t__ PLATFORM_SYSCALL_TRAP_NO ; 
 int /*<<< orphan*/  THROTTLE_LEVEL_NONE ; 
 int /*<<< orphan*/  assert (struct proc*) ; 
 TYPE_1__* current_thread () ; 
 struct proc* get_bsdthreadtask_info (TYPE_1__*) ; 
 int get_saved_state_svc_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_mach_absolute_time_trap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_mach_continuous_time_trap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_kauth_cred_uthread_update () ; 
 int /*<<< orphan*/  mach_syscall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  platform_syscall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscall_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_syscall (int /*<<< orphan*/ *,TYPE_1__*,struct uthread*,struct proc*) ; 

__attribute__((used)) static void
handle_svc(arm_saved_state_t *state)
{
	int trap_no = get_saved_state_svc_number(state);
	thread_t thread = current_thread();
	struct proc *p;

#define handle_svc_kprintf(x...) /* kprintf("handle_svc: " x) */

#define TRACE_SYSCALL 1
#if TRACE_SYSCALL
	syscall_trace(state);
#endif

	thread->iotier_override = THROTTLE_LEVEL_NONE; /* Reset IO tier override before handling SVC from userspace */

	if (trap_no == (int)PLATFORM_SYSCALL_TRAP_NO) {
		platform_syscall(state);
		panic("Returned from platform_syscall()?");
	}

	mach_kauth_cred_uthread_update();

	if (trap_no < 0) {
		if (trap_no == -3) {
			handle_mach_absolute_time_trap(state);
			return;
		} else if (trap_no == -4) {
			handle_mach_continuous_time_trap(state);
			return;
		}

		/* Counting perhaps better in the handler, but this is how it's been done */
		thread->syscalls_mach++;
		mach_syscall(state);
	} else {
		/* Counting perhaps better in the handler, but this is how it's been done */
		thread->syscalls_unix++;
		p = get_bsdthreadtask_info(thread);

		assert(p);

		unix_syscall(state, thread, (struct uthread*)thread->uthread, p);
	}
}