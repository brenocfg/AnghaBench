#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; } ;
typedef  TYPE_1__ TrackerTaskState ;
struct TYPE_6__ {int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; } ;
typedef  TYPE_2__ Task ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static TrackerTaskState *
TrackerTaskStateHashLookup(HTAB *taskStateHash, Task *task)
{
	TrackerTaskState *taskState = NULL;
	void *hashKey = NULL;
	bool handleFound = false;

	TrackerTaskState taskStateKey;
	taskStateKey.jobId = task->jobId;
	taskStateKey.taskId = task->taskId;

	hashKey = (void *) &taskStateKey;
	taskState = (TrackerTaskState *) hash_search(taskStateHash, hashKey,
												 HASH_FIND, &handleFound);

	return taskState;
}