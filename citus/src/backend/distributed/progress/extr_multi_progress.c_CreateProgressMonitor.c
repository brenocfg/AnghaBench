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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  dsm_handle ;
struct TYPE_4__ {int stepCount; int /*<<< orphan*/  processId; } ;
typedef  int Size ;
typedef  TYPE_1__ ProgressMonitorData ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  DSM_CREATE_NULL_IF_MAXSEGMENTS ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* MonitorDataFromDSMHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MyProcPid ; 
 int /*<<< orphan*/  PROGRESS_COMMAND_VACUUM ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  currentProgressDSMHandle ; 
 int /*<<< orphan*/ * dsm_create (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_segment_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pgstat_progress_start_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_progress_update_param (int,int /*<<< orphan*/ ) ; 

ProgressMonitorData *
CreateProgressMonitor(uint64 progressTypeMagicNumber, int stepCount, Size stepSize,
					  Oid relationId)
{
	dsm_segment *dsmSegment = NULL;
	dsm_handle dsmHandle = 0;
	ProgressMonitorData *monitor = NULL;
	Size monitorSize = 0;

	if (stepSize <= 0 || stepCount <= 0)
	{
		ereport(ERROR,
				(errmsg("number of steps and size of each step should be "
						"positive values")));
	}

	monitorSize = sizeof(ProgressMonitorData) + stepSize * stepCount;
	dsmSegment = dsm_create(monitorSize, DSM_CREATE_NULL_IF_MAXSEGMENTS);

	if (dsmSegment == NULL)
	{
		ereport(WARNING,
				(errmsg("could not create a dynamic shared memory segment to "
						"keep track of progress of the current command")));
		return NULL;
	}

	dsmHandle = dsm_segment_handle(dsmSegment);

	monitor = MonitorDataFromDSMHandle(dsmHandle, &dsmSegment);

	monitor->stepCount = stepCount;
	monitor->processId = MyProcPid;

	pgstat_progress_start_command(PROGRESS_COMMAND_VACUUM, relationId);
	pgstat_progress_update_param(1, dsmHandle);
	pgstat_progress_update_param(0, progressTypeMagicNumber);

	currentProgressDSMHandle = dsmHandle;

	return monitor;
}