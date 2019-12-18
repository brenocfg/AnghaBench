#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct exception_action {TYPE_2__* port; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  size_t exception_type_t ;
struct TYPE_7__ {scalar_t__ ip_receiver; } ;
struct TYPE_6__ {scalar_t__ itk_space; } ;

/* Variables and functions */
 size_t EXC_CRASH ; 
 scalar_t__ IP_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* current_task () ; 
 scalar_t__ ip_active (TYPE_2__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

kern_return_t
check_exc_receiver_dependency(
	exception_type_t exception,
	struct exception_action *excp,
	lck_mtx_t *mutex)
{
	kern_return_t retval = KERN_SUCCESS;

	if (excp == NULL || exception != EXC_CRASH)
		return retval;

	task_t task = current_task();
	lck_mtx_lock(mutex);
	ipc_port_t xport = excp[exception].port;
	if ( IP_VALID(xport)
		     && ip_active(xport)
		     && task->itk_space == xport->ip_receiver)
		retval = KERN_FAILURE;
	lck_mtx_unlock(mutex);
	return retval;
}