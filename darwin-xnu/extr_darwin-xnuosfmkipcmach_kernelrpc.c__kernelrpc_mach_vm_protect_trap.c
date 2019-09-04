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
struct _kernelrpc_mach_vm_protect_args {int /*<<< orphan*/  new_protection; int /*<<< orphan*/  set_maximum; int /*<<< orphan*/  size; int /*<<< orphan*/  address; int /*<<< orphan*/  target; } ;
struct TYPE_5__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int MACH_SEND_INVALID_DEST ; 
 TYPE_1__* current_task () ; 
 int mach_vm_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* port_name_to_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_deallocate (TYPE_1__*) ; 

int
_kernelrpc_mach_vm_protect_trap(struct _kernelrpc_mach_vm_protect_args *args)
{
	task_t task = port_name_to_task(args->target);
	int rv = MACH_SEND_INVALID_DEST;

	if (task != current_task())
		goto done;

	rv = mach_vm_protect(task->map, args->address, args->size,
	    args->set_maximum, args->new_protection);
	
done:
	if (task)
		task_deallocate(task);
	return (rv);
}