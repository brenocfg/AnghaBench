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
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_5__ {int /*<<< orphan*/  itk_space; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_SPACE_NULL ; 
 TYPE_1__* TASK_NULL ; 
 TYPE_1__* convert_port_to_locked_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

ipc_space_t
convert_port_to_space(
	ipc_port_t	port)
{
	ipc_space_t space;
	task_t task;

	task = convert_port_to_locked_task(port);

	if (task == TASK_NULL)
		return IPC_SPACE_NULL;

	if (!task->active) {
		task_unlock(task);
		return IPC_SPACE_NULL;
	}
		
	space = task->itk_space;
	is_reference(space);
	task_unlock(task);
	return (space);
}