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
struct TYPE_4__ {int requiresMasterEvaluation; int deferredPruning; int /*<<< orphan*/ * partitionKeyValue; int /*<<< orphan*/ * taskList; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ Job ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;
typedef  int /*<<< orphan*/  Const ;

/* Variables and functions */
 int /*<<< orphan*/  CanShardPrune (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* CreateJob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExtractFirstDistributedTableId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExtractInsertPartitionKeyValue (int /*<<< orphan*/ *) ; 
 int IsMultiRowInsert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NormalizeMultiRowInsertTargetList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RebuildQueryStrings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RequiresMasterEvaluation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RouterInsertTaskList (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static Job *
RouterInsertJob(Query *originalQuery, Query *query, DeferredErrorMessage **planningError)
{
	Oid distributedTableId = ExtractFirstDistributedTableId(query);
	List *taskList = NIL;
	Job *job = NULL;
	bool requiresMasterEvaluation = false;
	bool deferredPruning = false;
	Const *partitionKeyValue = NULL;

	bool isMultiRowInsert = IsMultiRowInsert(query);
	if (isMultiRowInsert)
	{
		/* add default expressions to RTE_VALUES in multi-row INSERTs */
		NormalizeMultiRowInsertTargetList(originalQuery);
	}

	if (isMultiRowInsert || !CanShardPrune(distributedTableId, query))
	{
		/*
		 * If there is a non-constant (e.g. parameter, function call) in the partition
		 * column of the INSERT then we defer shard pruning until the executor where
		 * these values are known.
		 *
		 * XXX: We also defer pruning for multi-row INSERTs because of some current
		 * limitations with the way multi-row INSERTs are handled. Most notably, we
		 * don't evaluate functions in task->rowValuesList. Therefore we need to
		 * perform function evaluation before we can run RouterInsertTaskList.
		 */
		taskList = NIL;
		deferredPruning = true;

		/* must evaluate the non-constant in the partition column */
		requiresMasterEvaluation = true;
	}
	else
	{
		taskList = RouterInsertTaskList(query, planningError);
		if (*planningError)
		{
			return NULL;
		}

		/* determine whether there are function calls to evaluate */
		requiresMasterEvaluation = RequiresMasterEvaluation(originalQuery);
	}

	if (!requiresMasterEvaluation)
	{
		/* no functions or parameters, build the query strings upfront */
		RebuildQueryStrings(originalQuery, taskList);

		/* remember the partition column value */
		partitionKeyValue = ExtractInsertPartitionKeyValue(originalQuery);
	}

	job = CreateJob(originalQuery);
	job->taskList = taskList;
	job->requiresMasterEvaluation = requiresMasterEvaluation;
	job->deferredPruning = deferredPruning;
	job->partitionKeyValue = partitionKeyValue;

	return job;
}