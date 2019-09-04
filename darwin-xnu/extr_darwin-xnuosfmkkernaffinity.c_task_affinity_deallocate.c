#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  TYPE_2__* affinity_space_t ;
struct TYPE_8__ {scalar_t__ aspc_task_count; int /*<<< orphan*/  aspc_lock; int /*<<< orphan*/  aspc_affinities; } ;
struct TYPE_7__ {TYPE_2__* affinity_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  affinity_space_free (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 

void
task_affinity_deallocate(task_t	task)
{
	affinity_space_t	aspc = task->affinity_space;

	DBG("task_affinity_deallocate(%p) aspc %p task_count %d\n",
		task, aspc, aspc->aspc_task_count);

	lck_mtx_lock(&aspc->aspc_lock);
	if (--(aspc->aspc_task_count) == 0) {
		assert(queue_empty(&aspc->aspc_affinities));
		lck_mtx_unlock(&aspc->aspc_lock);
		affinity_space_free(aspc);
	} else {
		lck_mtx_unlock(&aspc->aspc_lock);
	}
}