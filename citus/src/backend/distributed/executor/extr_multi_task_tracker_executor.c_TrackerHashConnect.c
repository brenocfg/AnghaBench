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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ TrackerStatus ;
typedef  int /*<<< orphan*/  TaskTracker ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 long RemoteTaskCheckInterval ; 
 scalar_t__ TRACKER_CONNECTED ; 
 scalar_t__ TRACKER_CONNECTION_FAILED ; 
 scalar_t__ TrackerConnectPoll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_get_num_entries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 

__attribute__((used)) static void
TrackerHashConnect(HTAB *taskTrackerHash)
{
	uint32 taskTrackerCount = (uint32) hash_get_num_entries(taskTrackerHash);
	uint32 triedTrackerCount = 0;

	/* loop until we tried to connect to all task trackers */
	while (triedTrackerCount < taskTrackerCount)
	{
		TaskTracker *taskTracker = NULL;
		HASH_SEQ_STATUS status;
		long sleepIntervalPerCycle = 0;

		/* loop over the task tracker hash, and poll all trackers again */
		triedTrackerCount = 0;
		hash_seq_init(&status, taskTrackerHash);

		taskTracker = (TaskTracker *) hash_seq_search(&status);
		while (taskTracker != NULL)
		{
			TrackerStatus trackerStatus = TrackerConnectPoll(taskTracker);
			if (trackerStatus == TRACKER_CONNECTED ||
				trackerStatus == TRACKER_CONNECTION_FAILED)
			{
				triedTrackerCount++;
			}

			taskTracker = (TaskTracker *) hash_seq_search(&status);
		}

		/* sleep to avoid tight loop */
		sleepIntervalPerCycle = RemoteTaskCheckInterval * 1000L;
		pg_usleep(sleepIntervalPerCycle);
	}
}