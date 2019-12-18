#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
struct TYPE_20__ {int /*<<< orphan*/  specFlags; } ;
struct TYPE_21__ {scalar_t__ kernel_stack; TYPE_1__ machine; } ;
struct TYPE_19__ {scalar_t__ cpu_active_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_STACK_DEPTH ; 
 int /*<<< orphan*/  OnProc ; 
 TYPE_2__* Switch_context (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  act_machine_switch_pcb (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpu_number () ; 
 TYPE_13__* current_cpu_datap () ; 
 scalar_t__ current_stack_depth () ; 
 int /*<<< orphan*/  fpu_switch_context (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ kernel_stack_depth_max ; 
 int /*<<< orphan*/  kpc_off_cpu (TYPE_2__*) ; 
 int /*<<< orphan*/  ml_hv_cswitch (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pmap_switch_context (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

thread_t
machine_switch_context(
	thread_t			old,
	thread_continue_t	continuation,
	thread_t			new)
{
	assert(current_cpu_datap()->cpu_active_stack == old->kernel_stack);

#if KPC
	kpc_off_cpu(old);
#endif /* KPC */

	/*
	 *	Save FP registers if in use.
	 */
	fpu_switch_context(old, new);

	old->machine.specFlags &= ~OnProc;
	new->machine.specFlags |= OnProc;

	/*
	 * Monitor the stack depth and report new max,
	 * not worrying about races.
	 */
	vm_offset_t	depth = current_stack_depth();
	if (depth > kernel_stack_depth_max) {
		kernel_stack_depth_max = depth;
		KERNEL_DEBUG_CONSTANT(
			MACHDBG_CODE(DBG_MACH_SCHED, MACH_STACK_DEPTH),
			(long) depth, 0, 0, 0, 0);
	}

	/*
	 *	Switch address maps if need be, even if not switching tasks.
	 *	(A server activation may be "borrowing" a client map.)
	 */
	pmap_switch_context(old, new, cpu_number());

	/*
	 *	Load the rest of the user state for the new thread
	 */
	act_machine_switch_pcb(old, new);

#if HYPERVISOR
	ml_hv_cswitch(old, new);
#endif

	return(Switch_context(old, continuation, new));
}