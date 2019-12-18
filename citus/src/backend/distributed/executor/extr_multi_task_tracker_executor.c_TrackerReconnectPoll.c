#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TrackerStatus ;
struct TYPE_4__ {scalar_t__ trackerStatus; scalar_t__ connectPollCount; int /*<<< orphan*/  connectionFailureCount; int /*<<< orphan*/  connectionId; } ;
typedef  TYPE_1__ TaskTracker ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_CONNECTION_ID ; 
 int MultiClientConnectionUp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiClientDisconnect (int /*<<< orphan*/ ) ; 
 scalar_t__ TRACKER_CONNECTED ; 
 scalar_t__ TRACKER_CONNECTION_FAILED ; 
 scalar_t__ TRACKER_CONNECT_POLL ; 
 scalar_t__ TRACKER_CONNECT_START ; 
 scalar_t__ TrackerConnectPoll (TYPE_1__*) ; 

__attribute__((used)) static void
TrackerReconnectPoll(TaskTracker *taskTracker)
{
	TrackerStatus currentStatus = taskTracker->trackerStatus;
	if (currentStatus == TRACKER_CONNECTED)
	{
		bool connectionUp = MultiClientConnectionUp(taskTracker->connectionId);
		if (connectionUp)
		{
			taskTracker->trackerStatus = TRACKER_CONNECTED;
		}
		else
		{
			taskTracker->trackerStatus = TRACKER_CONNECTION_FAILED;

			/* we lost the connection underneath us, clean it up */
			MultiClientDisconnect(taskTracker->connectionId);
			taskTracker->connectionId = INVALID_CONNECTION_ID;
		}
	}
	else if (currentStatus == TRACKER_CONNECT_START ||
			 currentStatus == TRACKER_CONNECT_POLL)
	{
		taskTracker->trackerStatus = TrackerConnectPoll(taskTracker);
	}
	else if (currentStatus == TRACKER_CONNECTION_FAILED)
	{
		taskTracker->connectionFailureCount++;
		taskTracker->connectPollCount = 0;

		taskTracker->trackerStatus = TRACKER_CONNECT_START;
	}
}