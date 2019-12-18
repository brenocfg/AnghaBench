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
typedef  TYPE_1__* task_suspension_token_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;
struct TYPE_6__ {scalar_t__ itk_resume; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_TASK_RESUME ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  IP_VALID (scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 scalar_t__ ipc_port_make_sonce (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_suspension_token_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

ipc_port_t
convert_task_suspension_token_to_port(
	task_suspension_token_t		task)
{
	ipc_port_t port;

	task_lock(task);
	if (task->active) {
		if (task->itk_resume == IP_NULL) {
			task->itk_resume = ipc_port_alloc_kernel();
			if (!IP_VALID(task->itk_resume)) {
				panic("failed to create resume port");
			}

			ipc_kobject_set(task->itk_resume, (ipc_kobject_t) task, IKOT_TASK_RESUME);
		}

		/*
		 * Create a send-once right for each instance of a direct user-called
		 * task_suspend2 call. Each time one of these send-once rights is abandoned,
		 * the notification handler will resume the target task.
		 */
		port = ipc_port_make_sonce(task->itk_resume);
		assert(IP_VALID(port));
	} else {
		port = IP_NULL;
	}

	task_unlock(task);
	task_suspension_token_deallocate(task);

	return port;
}