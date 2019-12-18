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
struct _kernelrpc_mach_port_destruct_args {int /*<<< orphan*/  guard; int /*<<< orphan*/  srdelta; int /*<<< orphan*/  name; int /*<<< orphan*/  target; } ;
struct TYPE_5__ {int /*<<< orphan*/  itk_space; } ;

/* Variables and functions */
 int MACH_SEND_INVALID_DEST ; 
 TYPE_1__* current_task () ; 
 int mach_port_destruct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* port_name_to_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_deallocate (TYPE_1__*) ; 

int
_kernelrpc_mach_port_destruct_trap(struct _kernelrpc_mach_port_destruct_args *args)
{
	task_t task = port_name_to_task(args->target);
	int rv = MACH_SEND_INVALID_DEST;

	if (task != current_task())
		goto done;

	rv = mach_port_destruct(task->itk_space, args->name, args->srdelta, args->guard);
	
done:
	if (task)
		task_deallocate(task);
	return (rv);
}