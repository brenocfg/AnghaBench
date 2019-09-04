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
typedef  scalar_t__ ipc_port_t ;
struct TYPE_5__ {scalar_t__ itk_self; scalar_t__ itk_nself; scalar_t__ itk_resume; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_NONE ; 
 int /*<<< orphan*/  IKO_NULL ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  itk_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  itk_unlock (TYPE_1__*) ; 

void
ipc_task_disable(
	task_t		task)
{
	ipc_port_t kport;
	ipc_port_t nport;
	ipc_port_t rport;

	itk_lock(task);
	kport = task->itk_self;
	if (kport != IP_NULL)
		ipc_kobject_set(kport, IKO_NULL, IKOT_NONE);
	nport = task->itk_nself;
	if (nport != IP_NULL)
		ipc_kobject_set(nport, IKO_NULL, IKOT_NONE);

	rport = task->itk_resume;
	if (rport != IP_NULL) {
		/*
		 * From this point onwards this task is no longer accepting
		 * resumptions.
		 *
		 * There are still outstanding suspensions on this task,
		 * even as it is being torn down. Disconnect the task
		 * from the rport, thereby "orphaning" the rport. The rport 
		 * itself will go away only when the last suspension holder
		 * destroys his SO right to it -- when he either
		 * exits, or tries to actually use that last SO right to
		 * resume this (now non-existent) task.
		 */
		ipc_kobject_set(rport, IKO_NULL, IKOT_NONE);
	}
	itk_unlock(task);
}