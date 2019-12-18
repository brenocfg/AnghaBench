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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_6__ {int currentTaskIndex; int /*<<< orphan*/  connectionId; int /*<<< orphan*/  trackerStatus; int /*<<< orphan*/  workerPort; int /*<<< orphan*/  workerName; } ;
typedef  TYPE_1__ TaskTracker ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  TRACKER_CONNECT_START ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  WORKER_LENGTH ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TaskTracker *
TrackerHashEnter(HTAB *taskTrackerHash, char *nodeName, uint32 nodePort)
{
	TaskTracker *taskTracker = NULL;
	void *hashKey = NULL;
	bool handleFound = false;

	TaskTracker taskTrackerKey;
	memset(&taskTrackerKey, 0, sizeof(TaskTracker));
	strlcpy(taskTrackerKey.workerName, nodeName, WORKER_LENGTH);
	taskTrackerKey.workerPort = nodePort;

	hashKey = (void *) &taskTrackerKey;
	taskTracker = (TaskTracker *) hash_search(taskTrackerHash, hashKey,
											  HASH_ENTER, &handleFound);

	/* if same node appears twice, we overwrite previous entry */
	if (handleFound)
	{
		ereport(WARNING, (errmsg("multiple entries for task tracker: \"%s:%u\"",
								 nodeName, nodePort)));
	}

	/* init task tracker object with zeroed out task tracker key */
	memcpy(taskTracker, &taskTrackerKey, sizeof(TaskTracker));
	taskTracker->trackerStatus = TRACKER_CONNECT_START;
	taskTracker->connectionId = INVALID_CONNECTION_ID;
	taskTracker->currentTaskIndex = -1;

	return taskTracker;
}