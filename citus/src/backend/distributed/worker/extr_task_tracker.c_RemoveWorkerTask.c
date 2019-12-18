#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WorkerTask ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
RemoveWorkerTask(WorkerTask *workerTask, HTAB *WorkerTasksHash)
{
	void *hashKey = (void *) workerTask;

	WorkerTask *taskRemoved = hash_search(WorkerTasksHash, hashKey, HASH_REMOVE, NULL);
	if (taskRemoved == NULL)
	{
		ereport(FATAL, (errmsg("worker task hash corrupted")));
	}
}