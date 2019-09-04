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
typedef  scalar_t__ ipc_port_t ;
struct TYPE_6__ {scalar_t__ itk_self; } ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 scalar_t__ ipc_port_make_send (scalar_t__) ; 
 int /*<<< orphan*/  itk_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  itk_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_deallocate (TYPE_1__*) ; 

ipc_port_t
convert_task_to_port(
	task_t		task)
{
	ipc_port_t port;

	itk_lock(task);

	if (task->itk_self != IP_NULL)
		port = ipc_port_make_send(task->itk_self);
	else
		port = IP_NULL;

	itk_unlock(task);

	task_deallocate(task);
	return port;
}