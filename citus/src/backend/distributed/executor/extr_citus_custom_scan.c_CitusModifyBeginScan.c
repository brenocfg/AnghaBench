#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* state; } ;
struct TYPE_12__ {TYPE_3__ ps; } ;
struct TYPE_13__ {TYPE_1__ ss; } ;
struct TYPE_18__ {TYPE_2__ customScanState; TYPE_6__* distributedPlan; } ;
struct TYPE_17__ {int /*<<< orphan*/  relationIdList; TYPE_4__* workerJob; } ;
struct TYPE_16__ {int /*<<< orphan*/ * es_param_list_info; } ;
struct TYPE_15__ {int /*<<< orphan*/ * taskList; int /*<<< orphan*/  partitionKeyValue; scalar_t__ deferredPruning; scalar_t__ requiresMasterEvaluation; int /*<<< orphan*/ * jobQuery; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  TYPE_3__ PlanState ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ Job ;
typedef  TYPE_5__ EState ;
typedef  TYPE_6__ DistributedPlan ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  TYPE_7__ CitusScanState ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  AcquireMetadataLocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecuteMasterEvaluableFunctions (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ExtractInsertPartitionKeyValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FirstReplicaAssignTaskList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockPartitionsInRelationList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  RaiseDeferredError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RebuildQueryStrings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RouterInsertTaskList (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_6__* copyObject (TYPE_6__*) ; 

__attribute__((used)) static void
CitusModifyBeginScan(CustomScanState *node, EState *estate, int eflags)
{
	CitusScanState *scanState = (CitusScanState *) node;
	DistributedPlan *distributedPlan = NULL;
	Job *workerJob = NULL;
	Query *jobQuery = NULL;
	List *taskList = NIL;

	/*
	 * We must not change the distributed plan since it may be reused across multiple
	 * executions of a prepared statement. Instead we create a deep copy that we only
	 * use for the current execution.
	 */
	distributedPlan = scanState->distributedPlan = copyObject(scanState->distributedPlan);

	workerJob = distributedPlan->workerJob;
	jobQuery = workerJob->jobQuery;
	taskList = workerJob->taskList;

	if (workerJob->requiresMasterEvaluation)
	{
		PlanState *planState = &(scanState->customScanState.ss.ps);
		EState *executorState = planState->state;

		ExecuteMasterEvaluableFunctions(jobQuery, planState);

		/*
		 * We've processed parameters in ExecuteMasterEvaluableFunctions and
		 * don't need to send their values to workers, since they will be
		 * represented as constants in the deparsed query. To avoid sending
		 * parameter values, we set the parameter list to NULL.
		 */
		executorState->es_param_list_info = NULL;

		if (workerJob->deferredPruning)
		{
			DeferredErrorMessage *planningError = NULL;

			/* need to perform shard pruning, rebuild the task list from scratch */
			taskList = RouterInsertTaskList(jobQuery, &planningError);

			if (planningError != NULL)
			{
				RaiseDeferredError(planningError, ERROR);
			}

			workerJob->taskList = taskList;
			workerJob->partitionKeyValue = ExtractInsertPartitionKeyValue(jobQuery);
		}

		RebuildQueryStrings(jobQuery, taskList);
	}

	/* prevent concurrent placement changes */
	AcquireMetadataLocks(taskList);

	/*
	 * We are taking locks on partitions of partitioned tables. These locks are
	 * necessary for locking tables that appear in the SELECT part of the query.
	 */
	LockPartitionsInRelationList(distributedPlan->relationIdList, AccessShareLock);

	/* modify tasks are always assigned using first-replica policy */
	workerJob->taskList = FirstReplicaAssignTaskList(taskList);
}