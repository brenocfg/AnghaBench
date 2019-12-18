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
struct TYPE_4__ {int /*<<< orphan*/ * relationRestrictionContext; } ;
typedef  int /*<<< orphan*/  RelationRestrictionContext ;
typedef  TYPE_1__ PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ContainsMultipleDistributedRelations (TYPE_1__*) ; 
 int EquivalenceListContainsRelationsEquality (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
RestrictionEquivalenceForPartitionKeysViaEquivalances(PlannerRestrictionContext *
													  plannerRestrictionContext,
													  List *allAttributeEquivalenceList)
{
	RelationRestrictionContext *restrictionContext =
		plannerRestrictionContext->relationRestrictionContext;

	/* there is a single distributed relation, no need to continue */
	if (!ContainsMultipleDistributedRelations(plannerRestrictionContext))
	{
		return true;
	}

	return EquivalenceListContainsRelationsEquality(allAttributeEquivalenceList,
													restrictionContext);
}