#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rtable; } ;
struct TYPE_7__ {int /*<<< orphan*/  plannerRestrictionContext; scalar_t__ allDistributionKeysInQueryAreEqual; } ;
typedef  TYPE_1__ RecursivePlanningContext ;
typedef  TYPE_2__ Query ;

/* Variables and functions */
 int /*<<< orphan*/  AllDistributionKeysInSubqueryAreEqual (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ContainsSubquery (TYPE_2__*) ; 
 scalar_t__ FindNodeCheckInRangeTableList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsLocalTableRTE ; 

__attribute__((used)) static bool
ShouldRecursivelyPlanNonColocatedSubqueries(Query *subquery,
											RecursivePlanningContext *context)
{
	/*
	 * If the input query already contains the equality, simply return since it is not
	 * possible to find any non colocated subqueries.
	 */
	if (context->allDistributionKeysInQueryAreEqual)
	{
		return false;
	}

	/*
	 * This check helps us in two ways:
	 *   (i) We're not targeting queries that don't include subqueries at all,
	 *       they should go through regular planning.
	 *  (ii) Lower level subqueries are already recursively planned, so we should
	 *       only bother non-colocated subquery joins, which only happens when
	 *       there are subqueries.
	 */
	if (!ContainsSubquery(subquery))
	{
		return false;
	}

	/* direct joins with local tables are not supported by any of Citus planners */
	if (FindNodeCheckInRangeTableList(subquery->rtable, IsLocalTableRTE))
	{
		return false;
	}

	/*
	 * Finally, check whether this subquery contains distribution key equality or not.
	 */
	if (!AllDistributionKeysInSubqueryAreEqual(subquery,
											   context->plannerRestrictionContext))
	{
		return true;
	}

	return false;
}