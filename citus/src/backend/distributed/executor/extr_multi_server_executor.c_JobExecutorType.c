#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  consttype; int /*<<< orphan*/  constvalue; int /*<<< orphan*/  constisnull; } ;
struct TYPE_6__ {int routerExecutable; scalar_t__ modLevel; int /*<<< orphan*/ * insertSelectSubquery; TYPE_1__* workerJob; } ;
struct TYPE_5__ {int /*<<< orphan*/ * taskList; int /*<<< orphan*/ * dependedJobList; TYPE_3__* partitionKeyValue; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ MultiExecutorType ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ Job ;
typedef  TYPE_2__ DistributedPlan ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ Const ;

/* Variables and functions */
 int /*<<< orphan*/ * ActiveReadableWorkerNodeList () ; 
 int /*<<< orphan*/  ApplyLogRedaction (char*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DEBUG2 ; 
 char* DatumToString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnableRepartitionJoins ; 
 scalar_t__ IsLoggableLevel (int /*<<< orphan*/ ) ; 
 scalar_t__ MULTI_EXECUTOR_ADAPTIVE ; 
 scalar_t__ MULTI_EXECUTOR_COORDINATOR_INSERT_SELECT ; 
 scalar_t__ MULTI_EXECUTOR_TASK_TRACKER ; 
 double MaxTrackedTasksPerNode ; 
 scalar_t__ ROW_MODIFY_READONLY ; 
 scalar_t__ TaskExecutorType ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int list_length (int /*<<< orphan*/ *) ; 

MultiExecutorType
JobExecutorType(DistributedPlan *distributedPlan)
{
	Job *job = distributedPlan->workerJob;
	MultiExecutorType executorType = TaskExecutorType;
	bool routerExecutablePlan = distributedPlan->routerExecutable;

	/* debug distribution column value */
	if (routerExecutablePlan)
	{
		if (IsLoggableLevel(DEBUG2))
		{
			Const *partitionValueConst = job->partitionKeyValue;

			if (partitionValueConst != NULL && !partitionValueConst->constisnull)
			{
				Datum partitionColumnValue = partitionValueConst->constvalue;
				Oid partitionColumnType = partitionValueConst->consttype;
				char *partitionColumnString = DatumToString(partitionColumnValue,
															partitionColumnType);

				ereport(DEBUG2, (errmsg("Plan is router executable"),
								 errdetail("distribution column value: %s",
										   ApplyLogRedaction(partitionColumnString))));
			}
			else
			{
				ereport(DEBUG2, (errmsg("Plan is router executable")));
			}
		}

		return MULTI_EXECUTOR_ADAPTIVE;
	}

	if (distributedPlan->insertSelectSubquery != NULL)
	{
		/*
		 * Even if adaptiveExecutorEnabled, we go through
		 * MULTI_EXECUTOR_COORDINATOR_INSERT_SELECT because
		 * the executor already knows how to handle adaptive
		 * executor when necessary.
		 */
		return MULTI_EXECUTOR_COORDINATOR_INSERT_SELECT;
	}

	Assert(distributedPlan->modLevel == ROW_MODIFY_READONLY);

	if (executorType == MULTI_EXECUTOR_ADAPTIVE)
	{
		/* if we have repartition jobs with adaptive executor and repartition
		 * joins are not enabled, error out. Otherwise, switch to task-tracker
		 */
		int dependedJobCount = list_length(job->dependedJobList);
		if (dependedJobCount > 0)
		{
			if (!EnableRepartitionJoins)
			{
				ereport(ERROR, (errmsg(
									"the query contains a join that requires repartitioning"),
								errhint("Set citus.enable_repartition_joins to on "
										"to enable repartitioning")));
			}

			ereport(DEBUG1, (errmsg(
								 "cannot use adaptive executor with repartition jobs"),
							 errhint("Since you enabled citus.enable_repartition_joins "
									 "Citus chose to use task-tracker.")));
			return MULTI_EXECUTOR_TASK_TRACKER;
		}
	}
	else
	{
		List *workerNodeList = ActiveReadableWorkerNodeList();
		int workerNodeCount = list_length(workerNodeList);
		int taskCount = list_length(job->taskList);
		double tasksPerNode = taskCount / ((double) workerNodeCount);

		/* if we have more tasks per node than what can be tracked, warn the user */
		if (tasksPerNode >= MaxTrackedTasksPerNode)
		{
			ereport(WARNING, (errmsg("this query assigns more tasks per node than the "
									 "configured max_tracked_tasks_per_node limit")));
		}
	}

	return executorType;
}