#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ TrackerTaskState ;
struct TYPE_8__ {int /*<<< orphan*/ * taskStateHash; } ;
typedef  TYPE_2__ TaskTracker ;
struct TYPE_9__ {int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; } ;
typedef  TYPE_3__ Task ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_FILE_TRANSMIT_QUEUED ; 
 TYPE_1__* TaskStateHashEnter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
TrackerQueueFileTransmit(TaskTracker *transmitTracker, Task *task)
{
	HTAB *transmitStateHash = transmitTracker->taskStateHash;
	TrackerTaskState *transmitState = NULL;

	transmitState = TaskStateHashEnter(transmitStateHash, task->jobId, task->taskId);
	transmitState->status = TASK_FILE_TRANSMIT_QUEUED;
}