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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* thread_t ;
struct x86_kernel_state {unsigned long k_rip; unsigned long k_rbx; unsigned long k_rsp; unsigned long k_eip; unsigned long k_ebx; unsigned long k_esp; } ;
struct TYPE_5__ {int /*<<< orphan*/  kernel_stack; int /*<<< orphan*/  sched_pri; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_STACK_ATTACH ; 
 struct x86_kernel_state* STACK_IKS (int /*<<< orphan*/ ) ; 
 scalar_t__ Thread_continue ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_continue ; 
 int /*<<< orphan*/  thread_initialize_kernel_state (TYPE_1__*) ; 
 scalar_t__ thread_tid (TYPE_1__*) ; 

void
machine_stack_attach(
	thread_t		thread,
	vm_offset_t		stack)
{
	struct x86_kernel_state *statep;

	KERNEL_DEBUG(MACHDBG_CODE(DBG_MACH_SCHED, MACH_STACK_ATTACH),
		     (uintptr_t)thread_tid(thread), thread->priority,
		     thread->sched_pri, 0, 0);

	assert(stack);
	thread->kernel_stack = stack;
	thread_initialize_kernel_state(thread);

	statep = STACK_IKS(stack);
#if defined(__x86_64__)
	statep->k_rip = (unsigned long) Thread_continue;
	statep->k_rbx = (unsigned long) thread_continue;
	statep->k_rsp = (unsigned long) STACK_IKS(stack);
#else
	statep->k_eip = (unsigned long) Thread_continue;
	statep->k_ebx = (unsigned long) thread_continue;
	statep->k_esp = (unsigned long) STACK_IKS(stack);
#endif

	return;
}