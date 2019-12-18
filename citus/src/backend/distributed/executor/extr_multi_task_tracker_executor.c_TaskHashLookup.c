#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TaskType ;
struct TYPE_4__ {int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; int /*<<< orphan*/  taskType; } ;
typedef  TYPE_1__ TaskMapKey ;
struct TYPE_5__ {int /*<<< orphan*/ * task; } ;
typedef  TYPE_2__ TaskMapEntry ;
typedef  int /*<<< orphan*/  Task ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Task *
TaskHashLookup(HTAB *taskHash, TaskType taskType, uint64 jobId, uint32 taskId)
{
	TaskMapEntry *taskEntry = NULL;
	Task *task = NULL;
	void *hashKey = NULL;
	bool handleFound = false;

	TaskMapKey taskKey;
	memset(&taskKey, 0, sizeof(TaskMapKey));

	taskKey.taskType = taskType;
	taskKey.jobId = jobId;
	taskKey.taskId = taskId;

	hashKey = (void *) &taskKey;
	taskEntry = (TaskMapEntry *) hash_search(taskHash, hashKey, HASH_FIND, &handleFound);

	if (taskEntry != NULL)
	{
		task = taskEntry->task;
	}

	return task;
}