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
struct _kernelrpc_mach_port_construct_args {int /*<<< orphan*/  name; int /*<<< orphan*/  context; int /*<<< orphan*/  options; int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  options ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  mach_port_options_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
struct TYPE_5__ {int /*<<< orphan*/  itk_space; } ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int MACH_SEND_INVALID_DATA ; 
 int MACH_SEND_INVALID_DEST ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,char*,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* current_task () ; 
 int mach_port_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* port_name_to_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_deallocate (TYPE_1__*) ; 

int
_kernelrpc_mach_port_construct_trap(struct _kernelrpc_mach_port_construct_args *args)
{
	task_t task = port_name_to_task(args->target);
	mach_port_name_t name;
	int rv = MACH_SEND_INVALID_DEST;
	mach_port_options_t options;

	if (copyin(args->options, (char *)&options, sizeof (options))) {
		rv = MACH_SEND_INVALID_DATA;
		goto done;
	}

	if (task != current_task())
		goto done;

	rv = mach_port_construct(task->itk_space, &options, args->context, &name);
	if (rv == KERN_SUCCESS)
		rv = copyout(&name, args->name, sizeof (name));

done:
	if (task)
		task_deallocate(task);
	return (rv);
}