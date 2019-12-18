#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ anchorRelationRestrictionList; } ;
struct TYPE_14__ {int /*<<< orphan*/ * jointree; } ;
struct TYPE_13__ {int /*<<< orphan*/ * plannerRestrictionContext; } ;
typedef  TYPE_1__ RecursivePlanningContext ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  FromExpr ;
typedef  TYPE_3__ ColocatedJoinChecker ;

/* Variables and functions */
 TYPE_3__ CreateColocatedJoinChecker (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  RecursivelyPlanNonColocatedJoinWalker (int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  RecursivelyPlanNonColocatedSubqueriesInWhere (TYPE_2__*,TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static void
RecursivelyPlanNonColocatedSubqueries(Query *subquery, RecursivePlanningContext *context)
{
	ColocatedJoinChecker colocatedJoinChecker;

	FromExpr *joinTree = subquery->jointree;
	PlannerRestrictionContext *restrictionContext = NULL;

	/* create the context for the non colocated subquery planning */
	restrictionContext = context->plannerRestrictionContext;
	colocatedJoinChecker = CreateColocatedJoinChecker(subquery, restrictionContext);

	/*
	 * Although this is a rare case, we weren't able to pick an anchor
	 * range table entry, so we cannot continue.
	 */
	if (colocatedJoinChecker.anchorRelationRestrictionList == NIL)
	{
		return;
	}

	/* handle from clause subqueries first */
	RecursivelyPlanNonColocatedJoinWalker((Node *) joinTree, &colocatedJoinChecker,
										  context);

	/* handle subqueries in WHERE clause */
	RecursivelyPlanNonColocatedSubqueriesInWhere(subquery, &colocatedJoinChecker,
												 context);
}