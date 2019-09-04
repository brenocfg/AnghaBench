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
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_6__ {scalar_t__ active; int /*<<< orphan*/  ith_sself; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  THREAD_KERNEL_PORT 128 
 TYPE_1__* THREAD_NULL ; 
 int /*<<< orphan*/  ipc_port_copy_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 

kern_return_t
thread_get_special_port(
	thread_t		thread,
	int				which,
	ipc_port_t		*portp)
{
	kern_return_t	result = KERN_SUCCESS;
	ipc_port_t		*whichp;

	if (thread == THREAD_NULL)
		return (KERN_INVALID_ARGUMENT);

	switch (which) {

	case THREAD_KERNEL_PORT:
		whichp = &thread->ith_sself;
		break;

	default:
		return (KERN_INVALID_ARGUMENT);
	}

 	thread_mtx_lock(thread);

	if (thread->active)
		*portp = ipc_port_copy_send(*whichp);
	else
		result = KERN_FAILURE;

	thread_mtx_unlock(thread);

	return (result);
}