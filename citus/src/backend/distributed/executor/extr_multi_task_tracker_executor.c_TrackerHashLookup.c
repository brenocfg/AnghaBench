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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  workerPort; int /*<<< orphan*/  workerName; } ;
typedef  TYPE_1__ TaskTracker ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  WORKER_LENGTH ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TaskTracker *
TrackerHashLookup(HTAB *trackerHash, const char *nodeName, uint32 nodePort)
{
	TaskTracker *taskTracker = NULL;
	void *hashKey = NULL;
	bool handleFound = false;

	TaskTracker taskTrackerKey;
	memset(taskTrackerKey.workerName, 0, WORKER_LENGTH);
	strlcpy(taskTrackerKey.workerName, nodeName, WORKER_LENGTH);
	taskTrackerKey.workerPort = nodePort;

	hashKey = (void *) &taskTrackerKey;
	taskTracker = (TaskTracker *) hash_search(trackerHash, hashKey,
											  HASH_FIND, &handleFound);
	if (taskTracker == NULL || !handleFound)
	{
		ereport(ERROR, (errmsg("could not find task tracker for node \"%s:%u\"",
							   nodeName, nodePort)));
	}

	return taskTracker;
}