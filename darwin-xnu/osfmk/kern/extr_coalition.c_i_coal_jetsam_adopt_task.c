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
struct i_jetsam_coalition {int /*<<< orphan*/  other; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_2__* coalition_t ;
struct TYPE_7__ {size_t type; int /*<<< orphan*/  id; struct i_jetsam_coalition j; } ;
struct TYPE_6__ {int /*<<< orphan*/ * task_coalition; } ;

/* Variables and functions */
 size_t COALITION_TYPE_JETSAM ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coal_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid (TYPE_1__*) ; 

__attribute__((used)) static kern_return_t
i_coal_jetsam_adopt_task(coalition_t coal, task_t task)
{
	struct i_jetsam_coalition *cj;
	assert(coal && coal->type == COALITION_TYPE_JETSAM);

	cj = &coal->j;

	assert(queue_empty(&task->task_coalition[COALITION_TYPE_JETSAM]));

	/* put each task initially in the "other" list */
	enqueue_tail(&cj->other, &task->task_coalition[COALITION_TYPE_JETSAM]);
	coal_dbg("coalition %lld adopted PID:%d as UNDEF",
		 coal->id, task_pid(task));

	return KERN_SUCCESS;
}