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
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ semaphore_t ;
struct TYPE_6__ {int /*<<< orphan*/  semaphore_list; } ;

/* Variables and functions */
 scalar_t__ SEMASPERSPL ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  semaphore_destroy_internal (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  semaphore_lock (scalar_t__) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

void
semaphore_destroy_all(
	task_t			task)
{
	uint32_t count;
	spl_t spl_level;

	count = 0;
	task_lock(task);
	while (!queue_empty(&task->semaphore_list)) {
		semaphore_t semaphore;

		semaphore = (semaphore_t) queue_first(&task->semaphore_list);

		if (count == 0) 
			spl_level = splsched();
		semaphore_lock(semaphore);

		semaphore_destroy_internal(task, semaphore);
		/* semaphore unlocked */

		/* throttle number of semaphores per interrupt disablement */
		if (++count == SEMASPERSPL) {
			count = 0;
			splx(spl_level);
		}
	}
	if (count != 0)
		splx(spl_level);

	task_unlock(task);
}