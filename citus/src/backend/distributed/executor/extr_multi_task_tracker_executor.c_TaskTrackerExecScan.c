#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_11__ {int finishedRemoteScan; TYPE_2__* distributedPlan; } ;
struct TYPE_10__ {int /*<<< orphan*/  relationIdList; TYPE_1__* workerJob; } ;
struct TYPE_9__ {int /*<<< orphan*/ * jobQuery; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Job ;
typedef  TYPE_2__ DistributedPlan ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  TYPE_3__ CitusScanState ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 scalar_t__ ContainsReadIntermediateResultFunction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DisableLocalExecution () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ErrorIfLocalExecutionHappened () ; 
 int /*<<< orphan*/  LoadTuplesIntoTupleStore (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  LockPartitionsInRelationList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiTaskTrackerExecute (TYPE_1__*) ; 
 int /*<<< orphan*/  PrepareMasterJobDirectory (TYPE_1__*) ; 
 int /*<<< orphan*/ * ReturnTupleFromTuplestore (TYPE_3__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

TupleTableSlot *
TaskTrackerExecScan(CustomScanState *node)
{
	CitusScanState *scanState = (CitusScanState *) node;
	TupleTableSlot *resultSlot = NULL;

	if (!scanState->finishedRemoteScan)
	{
		DistributedPlan *distributedPlan = scanState->distributedPlan;
		Job *workerJob = distributedPlan->workerJob;
		Query *jobQuery = workerJob->jobQuery;

		ErrorIfLocalExecutionHappened();
		DisableLocalExecution();

		if (ContainsReadIntermediateResultFunction((Node *) jobQuery))
		{
			ereport(ERROR, (errmsg("Complex subqueries and CTEs are not supported when "
								   "task_executor_type is set to 'task-tracker'")));
		}

		/* we are taking locks on partitions of partitioned tables */
		LockPartitionsInRelationList(distributedPlan->relationIdList, AccessShareLock);

		PrepareMasterJobDirectory(workerJob);
		MultiTaskTrackerExecute(workerJob);

		LoadTuplesIntoTupleStore(scanState, workerJob);

		scanState->finishedRemoteScan = true;
	}

	resultSlot = ReturnTupleFromTuplestore(scanState);

	return resultSlot;
}