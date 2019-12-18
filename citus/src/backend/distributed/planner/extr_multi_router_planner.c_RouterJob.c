#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_22__ {int requiresMasterEvaluation; int /*<<< orphan*/  jobId; void* taskList; int /*<<< orphan*/ * partitionKeyValue; } ;
struct TYPE_21__ {int /*<<< orphan*/  relationRestrictionContext; } ;
struct TYPE_20__ {scalar_t__ commandType; } ;
struct TYPE_19__ {scalar_t__ rtekind; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  TYPE_2__ Query ;
typedef  TYPE_3__ PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ Job ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;
typedef  int /*<<< orphan*/  Const ;

/* Variables and functions */
 scalar_t__ CMD_SELECT ; 
 TYPE_4__* CreateJob (TYPE_2__*) ; 
 TYPE_1__* GetUpdateOrDeleteRTE (TYPE_2__*) ; 
 scalar_t__ INVALID_SHARD_ID ; 
 int /*<<< orphan*/  MODIFY_TASK ; 
 void* NIL ; 
 int /*<<< orphan*/ * PlanRouterQuery (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int,int*,int /*<<< orphan*/ **) ; 
 void* QueryPushdownSqlTaskList (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RTE_SUBQUERY ; 
 int /*<<< orphan*/  ReorderTaskPlacementsByTaskAssignmentPolicy (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RequiresMasterEvaluation (TYPE_2__*) ; 
 void* SingleShardModifyTaskList (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 void* SingleShardSelectTaskList (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TaskAssignmentPolicy ; 

__attribute__((used)) static Job *
RouterJob(Query *originalQuery, PlannerRestrictionContext *plannerRestrictionContext,
		  DeferredErrorMessage **planningError)
{
	Job *job = NULL;
	uint64 shardId = INVALID_SHARD_ID;
	List *placementList = NIL;
	List *relationShardList = NIL;
	List *prunedShardIntervalListList = NIL;
	bool replacePrunedQueryWithDummy = false;
	bool requiresMasterEvaluation = false;
	RangeTblEntry *updateOrDeleteRTE = NULL;
	bool isMultiShardModifyQuery = false;
	Const *partitionKeyValue = NULL;

	/* router planner should create task even if it doesn't hit a shard at all */
	replacePrunedQueryWithDummy = true;

	/* check if this query requires master evaluation */
	requiresMasterEvaluation = RequiresMasterEvaluation(originalQuery);

	(*planningError) = PlanRouterQuery(originalQuery, plannerRestrictionContext,
									   &placementList, &shardId, &relationShardList,
									   &prunedShardIntervalListList,
									   replacePrunedQueryWithDummy,
									   &isMultiShardModifyQuery,
									   &partitionKeyValue);
	if (*planningError)
	{
		return NULL;
	}

	job = CreateJob(originalQuery);
	job->partitionKeyValue = partitionKeyValue;

	updateOrDeleteRTE = GetUpdateOrDeleteRTE(originalQuery);

	/*
	 * If all of the shards are pruned, we replace the relation RTE into
	 * subquery RTE that returns no results. However, this is not useful
	 * for UPDATE and DELETE queries. Therefore, if we detect a UPDATE or
	 * DELETE RTE with subquery type, we just set task list to empty and return
	 * the job.
	 */
	if (updateOrDeleteRTE != NULL && updateOrDeleteRTE->rtekind == RTE_SUBQUERY)
	{
		job->taskList = NIL;
		return job;
	}

	if (originalQuery->commandType == CMD_SELECT)
	{
		job->taskList = SingleShardSelectTaskList(originalQuery, job->jobId,
												  relationShardList, placementList,
												  shardId);

		/*
		 * Queries to reference tables, or distributed tables with multiple replica's have
		 * their task placements reordered according to the configured
		 * task_assignment_policy. This is only applicable to select queries as the modify
		 * queries will _always_ be executed on all placements.
		 *
		 * We also ignore queries that are targeting only intermediate results (e.g., no
		 * valid anchorShardId).
		 */
		if (shardId != INVALID_SHARD_ID)
		{
			ReorderTaskPlacementsByTaskAssignmentPolicy(job, TaskAssignmentPolicy,
														placementList);
		}
	}
	else if (isMultiShardModifyQuery)
	{
		job->taskList = QueryPushdownSqlTaskList(originalQuery, job->jobId,
												 plannerRestrictionContext->
												 relationRestrictionContext,
												 prunedShardIntervalListList,
												 MODIFY_TASK,
												 requiresMasterEvaluation);
	}
	else
	{
		job->taskList = SingleShardModifyTaskList(originalQuery, job->jobId,
												  relationShardList, placementList,
												  shardId);
	}

	job->requiresMasterEvaluation = requiresMasterEvaluation;
	return job;
}