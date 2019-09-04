#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_3__* coalition_t ;
struct TYPE_7__ {TYPE_2__* leader; } ;
struct TYPE_9__ {size_t type; TYPE_1__ j; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int /*<<< orphan*/ * task_coalition; TYPE_3__** coalition; } ;

/* Variables and functions */
 size_t COALITION_TYPE_JETSAM ; 
 size_t COALITION_TYPE_RESOURCE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  coal_dbg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  queue_chain_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid (TYPE_2__*) ; 

__attribute__((used)) static kern_return_t
i_coal_jetsam_remove_task(coalition_t coal, task_t task)
{
	assert(coal && coal->type == COALITION_TYPE_JETSAM);
	assert(task->coalition[COALITION_TYPE_JETSAM] == coal);

	coal_dbg("removing PID:%d from coalition id:%lld",
		 task_pid(task), coal->id);

	if (task == coal->j.leader) {
		coal->j.leader = NULL;
		coal_dbg("    PID:%d was the leader!", task_pid(task));
	} else {
		assert(!queue_empty(&task->task_coalition[COALITION_TYPE_JETSAM]));
	}

	/* remove the task from the specific coalition role queue */
	remqueue(&task->task_coalition[COALITION_TYPE_JETSAM]);
	queue_chain_init(task->task_coalition[COALITION_TYPE_RESOURCE]);

	return KERN_SUCCESS;
}