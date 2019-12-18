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
struct TYPE_10__ {TYPE_2__* subqueryPlannerRestriction; int /*<<< orphan*/ * anchorAttributeEquivalences; int /*<<< orphan*/ * anchorRelationRestrictionList; } ;
struct TYPE_9__ {TYPE_1__* relationRestrictionContext; } ;
struct TYPE_8__ {int /*<<< orphan*/ * relationRestrictionList; } ;
typedef  TYPE_1__ RelationRestrictionContext ;
typedef  int /*<<< orphan*/  Query ;
typedef  TYPE_2__ PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ ColocatedJoinChecker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* FilterPlannerRestrictionForQuery (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QueryContainsDistributedTableRTE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RestrictionEquivalenceForPartitionKeysViaEquivalances (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UnionRelationRestrictionLists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 
 void* palloc0 (int) ; 

bool
SubqueryColocated(Query *subquery, ColocatedJoinChecker *checker)
{
	List *anchorRelationRestrictionList = checker->anchorRelationRestrictionList;
	List *anchorAttributeEquivalances = checker->anchorAttributeEquivalences;

	PlannerRestrictionContext *restrictionContext = checker->subqueryPlannerRestriction;
	PlannerRestrictionContext *filteredPlannerContext =
		FilterPlannerRestrictionForQuery(restrictionContext, subquery);
	List *filteredRestrictionList =
		filteredPlannerContext->relationRestrictionContext->relationRestrictionList;

	List *unionedRelationRestrictionList = NULL;
	RelationRestrictionContext *unionedRelationRestrictionContext = NULL;
	PlannerRestrictionContext *unionedPlannerRestrictionContext = NULL;

	/*
	 * There are no relations in the input subquery, such as a subquery
	 * that consist of only intermediate results or without FROM
	 * clause.
	 */
	if (list_length(filteredRestrictionList) == 0)
	{
		Assert(!QueryContainsDistributedTableRTE(subquery));

		return true;
	}

	/*
	 * We merge the relation restrictions of the input subquery and the anchor
	 * restrictions to form a temporary relation restriction context. The aim of
	 * forming this temporary context is to check whether the context contains
	 * distribution key equality or not.
	 */
	unionedRelationRestrictionList =
		UnionRelationRestrictionLists(anchorRelationRestrictionList,
									  filteredRestrictionList);

	/*
	 * We already have the attributeEquivalances, thus, only need to prepare
	 * the planner restrictions with unioned relations for our purpose of
	 * distribution key equality. Note that we don't need to calculate the
	 * join restrictions, we're already relying on the attributeEquivalances
	 * provided by the context.
	 */
	unionedRelationRestrictionContext = palloc0(sizeof(RelationRestrictionContext));
	unionedRelationRestrictionContext->relationRestrictionList =
		unionedRelationRestrictionList;

	unionedPlannerRestrictionContext = palloc0(sizeof(PlannerRestrictionContext));
	unionedPlannerRestrictionContext->relationRestrictionContext =
		unionedRelationRestrictionContext;

	if (!RestrictionEquivalenceForPartitionKeysViaEquivalances(
			unionedPlannerRestrictionContext,
			anchorAttributeEquivalances))
	{
		return false;
	}

	return true;
}