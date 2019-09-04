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
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  t_kpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_KPC_FORCED_ALL_CTRS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
kpc_task_set_forced_all_ctrs(task_t task, boolean_t state)
{
	assert(task);

	task_lock(task);
	if (state)
		task->t_kpc |= TASK_KPC_FORCED_ALL_CTRS;
	else
		task->t_kpc &= ~TASK_KPC_FORCED_ALL_CTRS;
	task_unlock(task);
}