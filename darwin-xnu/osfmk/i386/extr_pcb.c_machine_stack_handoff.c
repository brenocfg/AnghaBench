#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_17__ {int /*<<< orphan*/  specFlags; } ;
struct TYPE_18__ {scalar_t__ kernel_stack; scalar_t__ reserved_stack; TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  OnProc ; 
 int /*<<< orphan*/  act_machine_switch_pcb (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  cpu_number () ; 
 int /*<<< orphan*/  fpu_switch_context (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  kpc_off_cpu (TYPE_2__*) ; 
 int /*<<< orphan*/  machine_set_current_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  ml_hv_cswitch (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pmap_switch_context (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_initialize_kernel_state (TYPE_2__*) ; 

void
machine_stack_handoff(thread_t old,
	      thread_t new)
{
	vm_offset_t     stack;

	assert(new);
	assert(old);

	kpc_off_cpu(old);

	stack = old->kernel_stack;
	if (stack == old->reserved_stack) {
		assert(new->reserved_stack);
		old->reserved_stack = new->reserved_stack;
		new->reserved_stack = stack;
	}
	old->kernel_stack = 0;
	/*
	 * A full call to machine_stack_attach() is unnecessry
	 * because old stack is already initialized.
	 */
	new->kernel_stack = stack;

	fpu_switch_context(old, new);
	
	old->machine.specFlags &= ~OnProc;
	new->machine.specFlags |= OnProc;

	pmap_switch_context(old, new, cpu_number());
	act_machine_switch_pcb(old, new);

#if HYPERVISOR
	ml_hv_cswitch(old, new);
#endif

	machine_set_current_thread(new);
	thread_initialize_kernel_state(new);

	return;
}