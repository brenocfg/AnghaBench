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
struct TYPE_9__ {int /*<<< orphan*/ * relationRestrictionContext; } ;
struct TYPE_8__ {scalar_t__ cteList; scalar_t__ setOperations; } ;
typedef  int /*<<< orphan*/  RelationRestrictionContext ;
typedef  TYPE_1__ Query ;
typedef  TYPE_2__ PlannerRestrictionContext ;

/* Variables and functions */
 scalar_t__ ContainsUnionSubquery (TYPE_1__*) ; 
 scalar_t__ ContextContainsLocalRelation (int /*<<< orphan*/ *) ; 
 scalar_t__ NIL ; 
 int RestrictionEquivalenceForPartitionKeys (TYPE_2__*) ; 
 int SafeToPushdownUnionSubquery (TYPE_2__*) ; 

bool
AllDistributionKeysInQueryAreEqual(Query *originalQuery,
								   PlannerRestrictionContext *plannerRestrictionContext)
{
	bool restrictionEquivalenceForPartitionKeys = false;
	RelationRestrictionContext *restrictionContext = NULL;

	/* we don't support distribution key equality checks for CTEs yet */
	if (originalQuery->cteList != NIL)
	{
		return false;
	}

	/* we don't support distribution key equality checks for local tables */
	restrictionContext = plannerRestrictionContext->relationRestrictionContext;
	if (ContextContainsLocalRelation(restrictionContext))
	{
		return false;
	}

	restrictionEquivalenceForPartitionKeys =
		RestrictionEquivalenceForPartitionKeys(plannerRestrictionContext);
	if (restrictionEquivalenceForPartitionKeys)
	{
		return true;
	}

	if (originalQuery->setOperations || ContainsUnionSubquery(originalQuery))
	{
		return SafeToPushdownUnionSubquery(plannerRestrictionContext);
	}

	return false;
}