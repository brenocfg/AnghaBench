#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int uint64_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  memory_object_size_t ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/ * atm_task_descriptor_t ;
struct TYPE_7__ {int /*<<< orphan*/ * atm_context; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ATM_TASK_DESCRIPTOR_NULL ; 
 int ATM_TRACE_DISABLE ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_NOT_SUPPORTED ; 
 scalar_t__ KERN_NO_SPACE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int MAX_TRACE_BUFFER_SIZE ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int atm_get_diagnostic_config () ; 
 int /*<<< orphan*/ * atm_task_descriptor_alloc_init (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  atm_task_descriptor_dealloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_map () ; 
 TYPE_1__* current_task () ; 
 scalar_t__ disable_atm ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 scalar_t__ mach_make_memory_entry_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

kern_return_t
atm_register_trace_memory(
	task_t 			task,
	uint64_t 		trace_buffer_address,
	uint64_t 		buffer_size)
{
	atm_task_descriptor_t task_descriptor;
	mach_port_t trace_buffer = MACH_PORT_NULL;
	kern_return_t kr = KERN_SUCCESS;

	if (disable_atm || (atm_get_diagnostic_config() & ATM_TRACE_DISABLE))
		return KERN_NOT_SUPPORTED;

	if (task != current_task())
		return KERN_INVALID_ARGUMENT;

	if (task->atm_context != NULL
	    || (void *)trace_buffer_address == NULL
	    || buffer_size == 0
	    || (buffer_size & PAGE_MASK) != 0
	    || buffer_size > MAX_TRACE_BUFFER_SIZE) {
		return KERN_INVALID_ARGUMENT;
	}

	vm_map_t map = current_map();
	memory_object_size_t mo_size = (memory_object_size_t) buffer_size;
	kr = mach_make_memory_entry_64(map,
		                          &mo_size,
		                          (mach_vm_offset_t)trace_buffer_address,
		                          VM_PROT_READ,
		                          &trace_buffer,
		                          NULL);
	if (kr != KERN_SUCCESS)
		return kr;

	task_descriptor = atm_task_descriptor_alloc_init(trace_buffer, buffer_size, task);
	if (task_descriptor == ATM_TASK_DESCRIPTOR_NULL) {
		ipc_port_release_send(trace_buffer);
		return KERN_NO_SPACE;
	}

	task_lock(task);
	if (task->atm_context == NULL) {
		task->atm_context = task_descriptor;
		kr = KERN_SUCCESS;
	} else {
		kr = KERN_FAILURE;
	}
	task_unlock(task);

	if (kr != KERN_SUCCESS) {
		/* undo the mapping and allocations since we failed to hook descriptor to task */
		atm_task_descriptor_dealloc(task_descriptor);
	}
	return KERN_SUCCESS;
}