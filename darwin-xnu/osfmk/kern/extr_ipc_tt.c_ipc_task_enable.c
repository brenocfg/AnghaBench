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
typedef  int /*<<< orphan*/  ipc_kobject_t ;
struct TYPE_5__ {scalar_t__ itk_self; scalar_t__ itk_nself; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_TASK ; 
 int /*<<< orphan*/  IKOT_TASK_NAME ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  itk_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  itk_unlock (TYPE_1__*) ; 

void
ipc_task_enable(
	task_t		task)
{
	ipc_port_t kport;
	ipc_port_t nport;

	itk_lock(task);
	kport = task->itk_self;
	if (kport != IP_NULL)
		ipc_kobject_set(kport, (ipc_kobject_t) task, IKOT_TASK);
	nport = task->itk_nself;
	if (nport != IP_NULL)
		ipc_kobject_set(nport, (ipc_kobject_t) task, IKOT_TASK_NAME);
	itk_unlock(task);
}