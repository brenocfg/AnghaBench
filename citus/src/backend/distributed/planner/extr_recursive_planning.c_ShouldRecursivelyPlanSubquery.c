#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  rtable; } ;
struct TYPE_8__ {int /*<<< orphan*/  plannerRestrictionContext; int /*<<< orphan*/  allDistributionKeysInQueryAreEqual; } ;
typedef  TYPE_1__ RecursivePlanningContext ;
typedef  TYPE_2__ Query ;

/* Variables and functions */
 int /*<<< orphan*/  AllDistributionKeysInSubqueryAreEqual (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DeferErrorIfCannotPushdownSubquery (TYPE_2__*,int) ; 
 scalar_t__ FindNodeCheckInRangeTableList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsLocalTableRTE ; 
 scalar_t__ MULTI_EXECUTOR_TASK_TRACKER ; 
 scalar_t__ SingleRelationRepartitionSubquery (TYPE_2__*) ; 
 scalar_t__ TaskExecutorType ; 

__attribute__((used)) static bool
ShouldRecursivelyPlanSubquery(Query *subquery, RecursivePlanningContext *context)
{
	if (FindNodeCheckInRangeTableList(subquery->rtable, IsLocalTableRTE))
	{
		/*
		 * Postgres can always plan queries that don't require distributed planning.
		 * Note that we need to check this first, otherwise the calls to the many other
		 * Citus planner functions would error our due to local relations.
		 *
		 * TODO: We could only successfully create distributed plans with local tables
		 * when the local tables are on the leaf queries and the upper level queries
		 * do not contain any other local tables.
		 */
	}
	else if (DeferErrorIfCannotPushdownSubquery(subquery, false) == NULL)
	{
		/*
		 * We should do one more check for the distribution key equality.
		 *
		 * If the input query to the planner doesn't contain distribution key equality,
		 * we should further check whether this individual subquery contains or not.
		 *
		 * If all relations are not joined on their distribution keys for the given
		 * subquery, we cannot push push it down and therefore we should try to
		 * recursively plan it.
		 */
		if (!context->allDistributionKeysInQueryAreEqual &&
			!AllDistributionKeysInSubqueryAreEqual(subquery,
												   context->plannerRestrictionContext))
		{
			return true;
		}

		/*
		 * Citus can pushdown this subquery, no need to recursively
		 * plan which is much expensive than pushdown.
		 */
		return false;
	}
	else if (TaskExecutorType == MULTI_EXECUTOR_TASK_TRACKER &&
			 SingleRelationRepartitionSubquery(subquery))
	{
		/*
		 * Citus can plan this and execute via repartitioning. Thus,
		 * no need to recursively plan.
		 */
		return false;
	}

	return true;
}