#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ setOperations; } ;
struct TYPE_9__ {scalar_t__ level; int /*<<< orphan*/  plannerRestrictionContext; } ;
struct TYPE_8__ {scalar_t__ op; } ;
typedef  TYPE_1__ SetOperationStmt ;
typedef  TYPE_2__ RecursivePlanningContext ;
typedef  TYPE_3__ Query ;
typedef  int /*<<< orphan*/  PlannerRestrictionContext ;

/* Variables and functions */
 int /*<<< orphan*/ * DeferErrorIfUnsupportedUnionQuery (TYPE_3__*) ; 
 int /*<<< orphan*/ * FilterPlannerRestrictionForQuery (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ SETOP_UNION ; 
 int /*<<< orphan*/  SafeToPushdownUnionSubquery (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ShouldRecursivelyPlanSetOperation(Query *query, RecursivePlanningContext *context)
{
	PlannerRestrictionContext *filteredRestrictionContext = NULL;

	SetOperationStmt *setOperations = (SetOperationStmt *) query->setOperations;
	if (setOperations == NULL)
	{
		return false;
	}

	if (context->level == 0)
	{
		/*
		 * We cannot push down top-level set operation. Recursively plan the
		 * leaf nodes such that it becomes a router query.
		 */
		return true;
	}

	if (setOperations->op != SETOP_UNION)
	{
		/*
		 * We can only push down UNION operaionts, plan other set operations
		 * recursively.
		 */
		return true;
	}

	if (DeferErrorIfUnsupportedUnionQuery(query) != NULL)
	{
		/*
		 * If at least one leaf query in the union is recurring, then all
		 * leaf nodes need to be recurring.
		 */
		return true;
	}

	filteredRestrictionContext =
		FilterPlannerRestrictionForQuery(context->plannerRestrictionContext, query);
	if (!SafeToPushdownUnionSubquery(filteredRestrictionContext))
	{
		/*
		 * The distribution column is not in the same place in all sides
		 * of the union, meaning we cannot determine distribution column
		 * equivalence. Recursive planning is necessary.
		 */
		return true;
	}

	return false;
}