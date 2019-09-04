#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_3__* thread_t ;
struct thread_kernel_state {int dummy; } ;
typedef  int /*<<< orphan*/  cpu_data_t ;
struct TYPE_12__ {int /*<<< orphan*/ * CpuDatap; scalar_t__ kstackptr; } ;
struct TYPE_13__ {scalar_t__ reserved_stack; TYPE_2__ machine; TYPE_1__* map; scalar_t__ kernel_stack; } ;
struct TYPE_11__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/ * getCpuDatap () ; 
 scalar_t__ kernel_stack_size ; 
 int /*<<< orphan*/  kpc_off_cpu (TYPE_3__*) ; 
 int /*<<< orphan*/  machine_set_current_thread (TYPE_3__*) ; 
 scalar_t__ machine_stack_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  pmap_set_pmap (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  thread_initialize_kernel_state (TYPE_3__*) ; 

void
machine_stack_handoff(
		      thread_t old,
		      thread_t new)
{
	vm_offset_t     stack;
	cpu_data_t	*cpu_data_ptr;

	kpc_off_cpu(old);

	stack = machine_stack_detach(old);
	cpu_data_ptr = getCpuDatap();
	new->kernel_stack = stack;
	new->machine.kstackptr = stack + kernel_stack_size - sizeof(struct thread_kernel_state);
	if (stack == old->reserved_stack) {
		assert(new->reserved_stack);
		old->reserved_stack = new->reserved_stack;
		new->reserved_stack = stack;
	}

	pmap_set_pmap(new->map->pmap, new);
	new->machine.CpuDatap = cpu_data_ptr;
	machine_set_current_thread(new);
	thread_initialize_kernel_state(new);

	return;
}