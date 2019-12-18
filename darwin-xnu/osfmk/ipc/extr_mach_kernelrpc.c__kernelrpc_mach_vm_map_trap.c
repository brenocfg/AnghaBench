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
typedef  TYPE_1__* task_t ;
struct _kernelrpc_mach_vm_map_trap_args {int /*<<< orphan*/  addr; int /*<<< orphan*/  cur_protection; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  size; int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_5__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IPC_PORT_NULL ; 
 int KERN_SUCCESS ; 
 int MACH_SEND_INVALID_DEST ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,char*,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* current_task () ; 
 int mach_vm_map_external (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* port_name_to_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_deallocate (TYPE_1__*) ; 

int
_kernelrpc_mach_vm_map_trap(struct _kernelrpc_mach_vm_map_trap_args *args)
{
	mach_vm_offset_t addr;
	task_t task = port_name_to_task(args->target);
	int rv = MACH_SEND_INVALID_DEST;

	if (task != current_task())
		goto done;

	if (copyin(args->addr, (char *)&addr, sizeof (addr)))
		goto done;

	rv = mach_vm_map_external(task->map, &addr, args->size, args->mask, args->flags,
			IPC_PORT_NULL, 0, FALSE, args->cur_protection, VM_PROT_ALL,
			VM_INHERIT_DEFAULT);
	if (rv == KERN_SUCCESS)
		rv = copyout(&addr, args->addr, sizeof (addr));

done:
	if (task)
		task_deallocate(task);
	return (rv);
}