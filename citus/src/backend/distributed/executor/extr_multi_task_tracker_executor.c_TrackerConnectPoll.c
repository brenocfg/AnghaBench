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
typedef  void* int32 ;
typedef  int TrackerStatus ;
struct TYPE_3__ {int trackerStatus; char* workerName; char* userName; int /*<<< orphan*/  connectPollCount; void* connectionId; int /*<<< orphan*/  workerPort; } ;
typedef  TYPE_1__ TaskTracker ;
typedef  int /*<<< orphan*/  ConnectStatus ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_CONNECTION_BAD ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_BUSY ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_BUSY_READ ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_BUSY_WRITE ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_READY ; 
 char* CurrentDatabaseName () ; 
 int /*<<< orphan*/  FATAL ; 
 void* INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  MultiClientConnectPoll (void*) ; 
 void* MultiClientConnectStart (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  MultiClientDisconnect (void*) ; 
 float NodeConnectionTimeout ; 
 float RemoteTaskCheckInterval ; 
#define  TRACKER_CONNECTED 131 
#define  TRACKER_CONNECTION_FAILED 130 
#define  TRACKER_CONNECT_POLL 129 
#define  TRACKER_CONNECT_START 128 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ceil (float) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 

__attribute__((used)) static TrackerStatus
TrackerConnectPoll(TaskTracker *taskTracker)
{
	switch (taskTracker->trackerStatus)
	{
		case TRACKER_CONNECT_START:
		{
			char *nodeName = taskTracker->workerName;
			uint32 nodePort = taskTracker->workerPort;
			char *nodeDatabase = CurrentDatabaseName();
			char *nodeUser = taskTracker->userName;

			int32 connectionId = MultiClientConnectStart(nodeName, nodePort,
														 nodeDatabase, nodeUser);
			if (connectionId != INVALID_CONNECTION_ID)
			{
				taskTracker->connectionId = connectionId;
				taskTracker->trackerStatus = TRACKER_CONNECT_POLL;
			}
			else
			{
				taskTracker->trackerStatus = TRACKER_CONNECTION_FAILED;
			}

			break;
		}

		case TRACKER_CONNECT_POLL:
		{
			int32 connectionId = taskTracker->connectionId;

			ConnectStatus pollStatus = MultiClientConnectPoll(connectionId);
			if (pollStatus == CLIENT_CONNECTION_READY)
			{
				taskTracker->trackerStatus = TRACKER_CONNECTED;
			}
			else if (pollStatus == CLIENT_CONNECTION_BUSY ||
					 pollStatus == CLIENT_CONNECTION_BUSY_READ ||
					 pollStatus == CLIENT_CONNECTION_BUSY_WRITE)
			{
				taskTracker->trackerStatus = TRACKER_CONNECT_POLL;
			}
			else if (pollStatus == CLIENT_CONNECTION_BAD)
			{
				taskTracker->trackerStatus = TRACKER_CONNECTION_FAILED;

				MultiClientDisconnect(connectionId);
				taskTracker->connectionId = INVALID_CONNECTION_ID;
			}

			/* now check if we have been trying to connect for too long */
			taskTracker->connectPollCount++;
			if (pollStatus == CLIENT_CONNECTION_BUSY_READ ||
				pollStatus == CLIENT_CONNECTION_BUSY_WRITE)
			{
				uint32 maxCount =
					ceil(NodeConnectionTimeout * 1.0f / RemoteTaskCheckInterval);
				uint32 currentCount = taskTracker->connectPollCount;
				if (currentCount >= maxCount)
				{
					ereport(WARNING, (errmsg("could not establish asynchronous "
											 "connection after %u ms",
											 NodeConnectionTimeout)));

					taskTracker->trackerStatus = TRACKER_CONNECTION_FAILED;

					MultiClientDisconnect(connectionId);
					taskTracker->connectionId = INVALID_CONNECTION_ID;
				}
			}

			break;
		}

		case TRACKER_CONNECTED:
		case TRACKER_CONNECTION_FAILED:
		{
			/* if connected or failed to connect in previous pass, reset poll count */
			taskTracker->connectPollCount = 0;
			break;
		}

		default:
		{
			int trackerStatus = (int) taskTracker->trackerStatus;
			ereport(FATAL, (errmsg("invalid task tracker status: %d", trackerStatus)));
			break;
		}
	}

	return taskTracker->trackerStatus;
}