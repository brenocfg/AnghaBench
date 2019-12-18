#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* workerJob; TYPE_2__* masterQuery; } ;
struct TYPE_8__ {TYPE_1__* jobQuery; int /*<<< orphan*/ * dependedJobList; int /*<<< orphan*/ * taskList; } ;
struct TYPE_7__ {int /*<<< orphan*/ * sortClause; } ;
struct TYPE_6__ {int hasAggs; } ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ Job ;
typedef  TYPE_4__ DistributedPlan ;

/* Variables and functions */
 int /*<<< orphan*/  EnableRouterExecution ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
DistributedPlanRouterExecutable(DistributedPlan *distributedPlan)
{
	Query *masterQuery = distributedPlan->masterQuery;
	Job *job = distributedPlan->workerJob;
	List *workerTaskList = job->taskList;
	int taskCount = list_length(workerTaskList);
	int dependedJobCount = list_length(job->dependedJobList);
	bool masterQueryHasAggregates = false;

	if (!EnableRouterExecution)
	{
		return false;
	}

	/* router executor cannot execute SELECT queries that hit more than one shard */
	if (taskCount != 1)
	{
		return false;
	}

	/* router executor cannot execute repartition jobs */
	if (dependedJobCount > 0)
	{
		return false;
	}

	/*
	 * Router executor does not run master query. This means that aggregation and
	 * sorting on the master query wouldn't be executed. Thus, such plans shouldn't be
	 * qualified as router executable.
	 */
	if (masterQuery != NULL && list_length(masterQuery->sortClause) > 0)
	{
		return false;
	}

	/*
	 * Note that worker query having an aggregate means that the master query should
	 * have either an aggregate or a function expression which has to be executed for
	 * the correct results.
	 */
	masterQueryHasAggregates = job->jobQuery->hasAggs;
	if (masterQueryHasAggregates)
	{
		return false;
	}

	return true;
}