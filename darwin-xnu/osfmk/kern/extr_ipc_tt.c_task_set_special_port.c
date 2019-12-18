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
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_6__ {scalar_t__ itk_self; int /*<<< orphan*/  itk_debug_control; int /*<<< orphan*/  itk_task_access; int /*<<< orphan*/  itk_seatbelt; int /*<<< orphan*/  itk_bootstrap; int /*<<< orphan*/  itk_host; int /*<<< orphan*/  itk_sself; } ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 scalar_t__ IP_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NO_ACCESS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  TASK_ACCESS_PORT 133 
#define  TASK_BOOTSTRAP_PORT 132 
#define  TASK_DEBUG_CONTROL_PORT 131 
#define  TASK_HOST_PORT 130 
#define  TASK_KERNEL_PORT 129 
 TYPE_1__* TASK_NULL ; 
#define  TASK_SEATBELT_PORT 128 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  itk_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  itk_unlock (TYPE_1__*) ; 

kern_return_t
task_set_special_port(
	task_t		task,
	int		which,
	ipc_port_t	port)
{
	ipc_port_t *whichp;
	ipc_port_t old;

	if (task == TASK_NULL)
		return KERN_INVALID_ARGUMENT;

	switch (which) {
	case TASK_KERNEL_PORT:
	    whichp = &task->itk_sself;
	    break;

	case TASK_HOST_PORT:
	    whichp = &task->itk_host;
	    break;

	case TASK_BOOTSTRAP_PORT:
	    whichp = &task->itk_bootstrap;
	    break;

	case TASK_SEATBELT_PORT:
	    whichp = &task->itk_seatbelt;
	    break;

	case TASK_ACCESS_PORT:
	    whichp = &task->itk_task_access;
	    break;

	case TASK_DEBUG_CONTROL_PORT:
	    whichp = &task->itk_debug_control;
	    break;

	default:
	    return KERN_INVALID_ARGUMENT;
	}/* switch */

	itk_lock(task);
	if (task->itk_self == IP_NULL) {
		itk_unlock(task);
		return KERN_FAILURE;
	}

	/* do not allow overwrite of seatbelt or task access ports */
	if ((TASK_SEATBELT_PORT == which  || TASK_ACCESS_PORT == which) 
		&& IP_VALID(*whichp)) {
			itk_unlock(task);
			return KERN_NO_ACCESS;
	}

	old = *whichp;
	*whichp = port;
	itk_unlock(task);

	if (IP_VALID(old))
		ipc_port_release_send(old);
	return KERN_SUCCESS;
}