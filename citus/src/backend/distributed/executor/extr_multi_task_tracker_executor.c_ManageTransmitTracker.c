#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_14__ {int /*<<< orphan*/  status; int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; } ;
typedef  TYPE_1__ TrackerTaskState ;
struct TYPE_15__ {int connectionBusy; TYPE_1__* connectionBusyOnTask; int /*<<< orphan*/  connectionId; int /*<<< orphan*/  taskStateHash; } ;
typedef  TYPE_2__ TaskTracker ;
struct TYPE_16__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__* StringInfo ;

/* Variables and functions */
 char* CurrentUserName () ; 
 TYPE_3__* JobDirectoryName (int /*<<< orphan*/ ) ; 
 int MultiClientSendQuery (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* NextQueuedFileTransmit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_ASSIGNED ; 
 int /*<<< orphan*/  TASK_CLIENT_SIDE_TRANSMIT_FAILED ; 
 int /*<<< orphan*/  TRANSMIT_WITH_USER_COMMAND ; 
 TYPE_3__* TaskFilename (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int TrackerConnectionUp (TYPE_2__*) ; 
 int TrackerHealthy (TYPE_2__*) ; 
 int /*<<< orphan*/  TrackerReconnectPoll (TYPE_2__*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_literal_cstr (char*) ; 

__attribute__((used)) static void
ManageTransmitTracker(TaskTracker *transmitTracker)
{
	TrackerTaskState *transmitState = NULL;
	bool trackerHealthy = false;
	bool trackerConnectionUp = false;

	trackerHealthy = TrackerHealthy(transmitTracker);
	if (!trackerHealthy)
	{
		return;
	}

	trackerConnectionUp = TrackerConnectionUp(transmitTracker);
	if (!trackerConnectionUp)
	{
		TrackerReconnectPoll(transmitTracker);  /* try an async reconnect */
		return;
	}

	/* connection belongs to another file transmit */
	if (transmitTracker->connectionBusy)
	{
		return;
	}

	transmitState = NextQueuedFileTransmit(transmitTracker->taskStateHash);
	if (transmitState != NULL)
	{
		bool fileTransmitStarted = false;
		int32 connectionId = transmitTracker->connectionId;
		StringInfo jobDirectoryName = JobDirectoryName(transmitState->jobId);
		StringInfo taskFilename = TaskFilename(jobDirectoryName, transmitState->taskId);
		char *userName = CurrentUserName();

		StringInfo fileTransmitQuery = makeStringInfo();
		appendStringInfo(fileTransmitQuery, TRANSMIT_WITH_USER_COMMAND,
						 taskFilename->data, quote_literal_cstr(userName));

		fileTransmitStarted = MultiClientSendQuery(connectionId, fileTransmitQuery->data);
		if (fileTransmitStarted)
		{
			transmitState->status = TASK_ASSIGNED;

			transmitTracker->connectionBusy = true;
			transmitTracker->connectionBusyOnTask = transmitState;
		}
		else
		{
			transmitState->status = TASK_CLIENT_SIDE_TRANSMIT_FAILED;

			transmitTracker->connectionBusy = false;
			transmitTracker->connectionBusyOnTask = NULL;
		}
	}
}