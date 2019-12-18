#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ContainsMultipleDistributedRelations (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GenerateAllAttributeEquivalences (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int RestrictionEquivalenceForPartitionKeysViaEquivalances (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
RestrictionEquivalenceForPartitionKeys(PlannerRestrictionContext *restrictionContext)
{
	List *attributeEquivalenceList = NIL;

	/* there is a single distributed relation, no need to continue */
	if (!ContainsMultipleDistributedRelations(restrictionContext))
	{
		return true;
	}

	attributeEquivalenceList = GenerateAllAttributeEquivalences(restrictionContext);

	return RestrictionEquivalenceForPartitionKeysViaEquivalances(restrictionContext,
																 attributeEquivalenceList);
}