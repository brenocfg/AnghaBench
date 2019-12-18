#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_6__ {TYPE_1__* relationRestrictionContext; } ;
struct TYPE_5__ {int /*<<< orphan*/  relationRestrictionList; } ;
typedef  TYPE_1__ RelationRestrictionContext ;
typedef  TYPE_2__ PlannerRestrictionContext ;

/* Variables and functions */
 int ReferenceRelationCount (TYPE_1__*) ; 
 int list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ContainsMultipleDistributedRelations(PlannerRestrictionContext *
									 plannerRestrictionContext)
{
	RelationRestrictionContext *restrictionContext =
		plannerRestrictionContext->relationRestrictionContext;

	uint32 referenceRelationCount = ReferenceRelationCount(restrictionContext);
	uint32 totalRelationCount = list_length(restrictionContext->relationRestrictionList);
	uint32 nonReferenceRelationCount = totalRelationCount - referenceRelationCount;

	/*
	 * If the query includes a single relation which is not a reference table,
	 * we should not check the partition column equality.
	 * Consider two example cases:
	 *   (i)   The query includes only a single colocated relation
	 *   (ii)  A colocated relation is joined with a (or multiple) reference
	 *         table(s) where colocated relation is not joined on the partition key
	 *
	 * For the above two cases, we don't need to execute the partition column equality
	 * algorithm. The reason is that the essence of this function is to ensure that the
	 * tasks that are going to be created should not need data from other tasks. In both
	 * cases mentioned above, the necessary data per task would be on available.
	 */
	if (nonReferenceRelationCount <= 1)
	{
		return false;
	}

	return true;
}