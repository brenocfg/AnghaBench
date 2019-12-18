#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; } ;
typedef  TYPE_1__ WorkerTask ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  TaskTrackerTaskHash ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

WorkerTask *
WorkerTasksHashFind(uint64 jobId, uint32 taskId)
{
	WorkerTask *workerTask = NULL;
	void *hashKey = NULL;

	WorkerTask searchTask;
	searchTask.jobId = jobId;
	searchTask.taskId = taskId;

	hashKey = (void *) &searchTask;
	workerTask = (WorkerTask *) hash_search(TaskTrackerTaskHash, hashKey,
											HASH_FIND, NULL);

	return workerTask;
}