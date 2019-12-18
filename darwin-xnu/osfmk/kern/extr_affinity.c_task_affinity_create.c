#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  TYPE_2__* affinity_space_t ;
struct TYPE_9__ {int /*<<< orphan*/  aspc_lock; int /*<<< orphan*/  aspc_task_count; } ;
struct TYPE_8__ {TYPE_2__* affinity_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
task_affinity_create(task_t parent_task, task_t child_task)
{
	affinity_space_t	aspc = parent_task->affinity_space;

	DBG("task_affinity_create(%p,%p)\n", parent_task, child_task);

	assert(aspc);

	/*
	 * Bump the task reference count on the shared namespace and
	 * give it to the child.
	 */
	lck_mtx_lock(&aspc->aspc_lock);
	aspc->aspc_task_count++;
	child_task->affinity_space = aspc;
	lck_mtx_unlock(&aspc->aspc_lock);
}