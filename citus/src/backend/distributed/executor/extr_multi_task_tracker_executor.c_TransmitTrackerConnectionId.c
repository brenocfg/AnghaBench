#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_6__ {scalar_t__ jobId; scalar_t__ taskId; } ;
typedef  TYPE_1__ TrackerTaskState ;
struct TYPE_7__ {int /*<<< orphan*/  connectionId; TYPE_1__* connectionBusyOnTask; } ;
typedef  TYPE_2__ TaskTracker ;
struct TYPE_8__ {scalar_t__ jobId; scalar_t__ taskId; } ;
typedef  TYPE_3__ Task ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_CONNECTION_ID ; 

__attribute__((used)) static int32
TransmitTrackerConnectionId(TaskTracker *transmitTracker, Task *task)
{
	int32 connectionId = INVALID_CONNECTION_ID;

	TrackerTaskState *transmitState = transmitTracker->connectionBusyOnTask;
	if (transmitState != NULL)
	{
		/* we are transmitting results for this particular task */
		if (transmitState->jobId == task->jobId &&
			transmitState->taskId == task->taskId)
		{
			connectionId = transmitTracker->connectionId;
		}
	}

	return connectionId;
}