#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  connectionId; int /*<<< orphan*/  taskStatus; } ;
typedef  TYPE_1__ WorkerTask ;
struct TYPE_5__ {int /*<<< orphan*/  taskHashLock; } ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  RESERVED_JOB_ID ; 
 int /*<<< orphan*/  SHUTDOWN_MARKER_TASK_ID ; 
 int /*<<< orphan*/  TASK_SUCCEEDED ; 
 TYPE_1__* WorkerTasksHashEnter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* WorkerTasksSharedState ; 

__attribute__((used)) static void
TrackerRegisterShutDown(HTAB *WorkerTasksHash)
{
	uint64 jobId = RESERVED_JOB_ID;
	uint32 taskId = SHUTDOWN_MARKER_TASK_ID;
	WorkerTask *shutdownMarkerTask = NULL;

	LWLockAcquire(&WorkerTasksSharedState->taskHashLock, LW_EXCLUSIVE);

	shutdownMarkerTask = WorkerTasksHashEnter(jobId, taskId);
	shutdownMarkerTask->taskStatus = TASK_SUCCEEDED;
	shutdownMarkerTask->connectionId = INVALID_CONNECTION_ID;

	LWLockRelease(&WorkerTasksSharedState->taskHashLock);
}