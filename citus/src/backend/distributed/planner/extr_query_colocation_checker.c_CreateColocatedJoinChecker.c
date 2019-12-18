#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * anchorAttributeEquivalences; void* anchorRelationRestrictionList; TYPE_3__* subqueryPlannerRestriction; int /*<<< orphan*/ * subquery; } ;
struct TYPE_14__ {TYPE_1__* relationRestrictionContext; } ;
struct TYPE_13__ {scalar_t__ rtekind; int /*<<< orphan*/ * subquery; } ;
struct TYPE_12__ {void* relationRestrictionList; } ;
typedef  TYPE_1__ RelationRestrictionContext ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  int /*<<< orphan*/  Query ;
typedef  TYPE_3__ PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ ColocatedJoinChecker ;

/* Variables and functions */
 TYPE_2__* AnchorRte (int /*<<< orphan*/ *) ; 
 TYPE_3__* FilterPlannerRestrictionForQuery (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GenerateAllAttributeEquivalences (TYPE_3__*) ; 
 void* NIL ; 
 scalar_t__ RTE_RELATION ; 
 scalar_t__ RTE_SUBQUERY ; 
 int /*<<< orphan*/ * WrapRteRelationIntoSubquery (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_unreachable () ; 

ColocatedJoinChecker
CreateColocatedJoinChecker(Query *subquery, PlannerRestrictionContext *restrictionContext)
{
	ColocatedJoinChecker colocatedJoinChecker;

	RangeTblEntry *anchorRangeTblEntry = NULL;
	Query *anchorSubquery = NULL;
	PlannerRestrictionContext *anchorPlannerRestrictionContext = NULL;
	RelationRestrictionContext *anchorRelationRestrictionContext = NULL;
	List *anchorRestrictionEquivalences = NIL;

	/* we couldn't pick an anchor subquery, no need to continue */
	anchorRangeTblEntry = AnchorRte(subquery);
	if (anchorRangeTblEntry == NULL)
	{
		colocatedJoinChecker.anchorRelationRestrictionList = NIL;

		return colocatedJoinChecker;
	}

	if (anchorRangeTblEntry->rtekind == RTE_RELATION)
	{
		/*
		 * If we get a relation as our anchor, wrap into a subquery. The only
		 * reason that we wrap the relation into a subquery is that some of the utility
		 * functions (i.e., FilterPlannerRestrictionForQuery()) rely on queries
		 * not relations.
		 */
		anchorSubquery = WrapRteRelationIntoSubquery(anchorRangeTblEntry);
	}
	else if (anchorRangeTblEntry->rtekind == RTE_SUBQUERY)
	{
		anchorSubquery = anchorRangeTblEntry->subquery;
	}
	else
	{
		/* we don't expect any other RTE type here */
		pg_unreachable();
	}

	anchorPlannerRestrictionContext =
		FilterPlannerRestrictionForQuery(restrictionContext, anchorSubquery);
	anchorRelationRestrictionContext =
		anchorPlannerRestrictionContext->relationRestrictionContext;
	anchorRestrictionEquivalences =
		GenerateAllAttributeEquivalences(anchorPlannerRestrictionContext);

	/* fill the non colocated planning context */
	colocatedJoinChecker.subquery = subquery;
	colocatedJoinChecker.subqueryPlannerRestriction = restrictionContext;

	colocatedJoinChecker.anchorRelationRestrictionList =
		anchorRelationRestrictionContext->relationRestrictionList;
	colocatedJoinChecker.anchorAttributeEquivalences = anchorRestrictionEquivalences;

	return colocatedJoinChecker;
}