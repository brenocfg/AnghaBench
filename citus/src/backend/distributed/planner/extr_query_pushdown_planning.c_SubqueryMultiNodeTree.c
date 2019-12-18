#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ rtekind; int /*<<< orphan*/ * subquery; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  MultiNode ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DeferErrorIfQueryNotSupported (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DeferErrorIfUnsupportedSubqueryPushdown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DeferErrorIfUnsupportedSubqueryRepartition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * MultiNodeTree (int /*<<< orphan*/ *) ; 
 scalar_t__ RTE_SUBQUERY ; 
 int /*<<< orphan*/  RaiseDeferredError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RaiseDeferredErrorInternal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SingleRelationRepartitionSubquery (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SubqueryEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SubqueryPushdownMultiNodeTree (int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 

MultiNode *
SubqueryMultiNodeTree(Query *originalQuery, Query *queryTree,
					  PlannerRestrictionContext *plannerRestrictionContext)
{
	MultiNode *multiQueryNode = NULL;
	DeferredErrorMessage *subqueryPushdownError = NULL;
	DeferredErrorMessage *unsupportedQueryError = NULL;

	/*
	 * This is a generic error check that applies to both subquery pushdown
	 * and single table repartition subquery.
	 */
	unsupportedQueryError = DeferErrorIfQueryNotSupported(originalQuery);
	if (unsupportedQueryError != NULL)
	{
		RaiseDeferredError(unsupportedQueryError, ERROR);
	}

	/*
	 * In principle, we're first trying subquery pushdown planner. If it fails
	 * to create a logical plan, continue with trying the single table
	 * repartition subquery planning.
	 */
	subqueryPushdownError = DeferErrorIfUnsupportedSubqueryPushdown(originalQuery,
																	plannerRestrictionContext);
	if (!subqueryPushdownError)
	{
		multiQueryNode = SubqueryPushdownMultiNodeTree(originalQuery);
	}
	else if (subqueryPushdownError)
	{
		bool singleRelationRepartitionSubquery = false;
		RangeTblEntry *subqueryRangeTableEntry = NULL;
		Query *subqueryTree = NULL;
		DeferredErrorMessage *repartitionQueryError = NULL;
		List *subqueryEntryList = NULL;

		/*
		 * If not eligible for single relation repartition query, we should raise
		 * subquery pushdown error.
		 */
		singleRelationRepartitionSubquery =
			SingleRelationRepartitionSubquery(originalQuery);
		if (!singleRelationRepartitionSubquery)
		{
			RaiseDeferredErrorInternal(subqueryPushdownError, ERROR);
		}

		subqueryEntryList = SubqueryEntryList(queryTree);
		subqueryRangeTableEntry = (RangeTblEntry *) linitial(subqueryEntryList);
		Assert(subqueryRangeTableEntry->rtekind == RTE_SUBQUERY);

		subqueryTree = subqueryRangeTableEntry->subquery;

		repartitionQueryError = DeferErrorIfUnsupportedSubqueryRepartition(subqueryTree);
		if (repartitionQueryError)
		{
			RaiseDeferredErrorInternal(repartitionQueryError, ERROR);
		}

		/* all checks has passed, safe to create the multi plan */
		multiQueryNode = MultiNodeTree(queryTree);
	}

	Assert(multiQueryNode != NULL);

	return multiQueryNode;
}