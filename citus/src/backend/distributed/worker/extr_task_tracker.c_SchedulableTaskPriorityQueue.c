#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {int /*<<< orphan*/  assignedAt; int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; } ;
typedef  TYPE_1__ WorkerTask ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CompareTasksByTime ; 
 int CountTasksMatchingCriteria (int /*<<< orphan*/ *,scalar_t__ (*) (TYPE_1__*)) ; 
 scalar_t__ SchedulableTask (TYPE_1__*) ; 
 TYPE_1__* WORKER_TASK_AT (TYPE_1__*,int) ; 
 int WORKER_TASK_SIZE ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WorkerTask *
SchedulableTaskPriorityQueue(HTAB *WorkerTasksHash)
{
	HASH_SEQ_STATUS status;
	WorkerTask *currentTask = NULL;
	WorkerTask *priorityQueue = NULL;
	uint32 queueSize = 0;
	uint32 queueIndex = 0;

	/* our priority queue size equals to the number of schedulable tasks */
	queueSize = CountTasksMatchingCriteria(WorkerTasksHash, &SchedulableTask);
	if (queueSize == 0)
	{
		return NULL;
	}

	/* allocate an array of tasks for our priority queue */
	priorityQueue = (WorkerTask *) palloc0(WORKER_TASK_SIZE * queueSize);

	/* copy tasks in the shared hash to the priority queue */
	hash_seq_init(&status, WorkerTasksHash);

	currentTask = (WorkerTask *) hash_seq_search(&status);
	while (currentTask != NULL)
	{
		if (SchedulableTask(currentTask))
		{
			/* tasks in the priority queue only need the first three fields */
			WorkerTask *queueTask = WORKER_TASK_AT(priorityQueue, queueIndex);

			queueTask->jobId = currentTask->jobId;
			queueTask->taskId = currentTask->taskId;
			queueTask->assignedAt = currentTask->assignedAt;

			queueIndex++;
		}

		currentTask = (WorkerTask *) hash_seq_search(&status);
	}

	/* now order elements in the queue according to our sorting criterion */
	qsort(priorityQueue, queueSize, WORKER_TASK_SIZE, CompareTasksByTime);

	return priorityQueue;
}