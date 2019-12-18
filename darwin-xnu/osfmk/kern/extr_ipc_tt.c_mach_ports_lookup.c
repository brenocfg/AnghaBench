#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  TYPE_1__* task_t ;
typedef  scalar_t__ mach_port_array_t ;
typedef  int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_6__ {scalar_t__ itk_self; int /*<<< orphan*/ * itk_registered; } ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* TASK_NULL ; 
 int TASK_PORT_REGISTER_MAX ; 
 int /*<<< orphan*/  ipc_port_copy_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  itk_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  itk_unlock (TYPE_1__*) ; 
 void* kalloc (scalar_t__) ; 
 int /*<<< orphan*/  kfree (void*,scalar_t__) ; 

kern_return_t
mach_ports_lookup(
	task_t			task,
	mach_port_array_t	*portsp,
	mach_msg_type_number_t	*portsCnt)
{
	void  *memory;
	vm_size_t size;
	ipc_port_t *ports;
	int i;

	if (task == TASK_NULL)
		return KERN_INVALID_ARGUMENT;

	size = (vm_size_t) (TASK_PORT_REGISTER_MAX * sizeof(ipc_port_t));

	memory = kalloc(size);
	if (memory == 0)
		return KERN_RESOURCE_SHORTAGE;

	itk_lock(task);
	if (task->itk_self == IP_NULL) {
		itk_unlock(task);

		kfree(memory, size);
		return KERN_INVALID_ARGUMENT;
	}

	ports = (ipc_port_t *) memory;

	/*
	 *	Clone port rights.  Because kalloc'd memory
	 *	is wired, we won't fault while holding the task lock.
	 */

	for (i = 0; i < TASK_PORT_REGISTER_MAX; i++)
		ports[i] = ipc_port_copy_send(task->itk_registered[i]);

	itk_unlock(task);

	*portsp = (mach_port_array_t) ports;
	*portsCnt = TASK_PORT_REGISTER_MAX;
	return KERN_SUCCESS;
}