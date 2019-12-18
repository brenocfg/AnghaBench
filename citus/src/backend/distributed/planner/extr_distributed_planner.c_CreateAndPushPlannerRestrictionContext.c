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
struct TYPE_6__ {TYPE_1__* relationRestrictionContext; int /*<<< orphan*/  memoryContext; void* joinRestrictionContext; } ;
struct TYPE_5__ {int allReferenceTables; } ;
typedef  int /*<<< orphan*/  RelationRestrictionContext ;
typedef  TYPE_2__ PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  JoinRestrictionContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  lcons (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* palloc0 (int) ; 
 int /*<<< orphan*/  plannerRestrictionContextList ; 

__attribute__((used)) static PlannerRestrictionContext *
CreateAndPushPlannerRestrictionContext(void)
{
	PlannerRestrictionContext *plannerRestrictionContext =
		palloc0(sizeof(PlannerRestrictionContext));

	plannerRestrictionContext->relationRestrictionContext =
		palloc0(sizeof(RelationRestrictionContext));

	plannerRestrictionContext->joinRestrictionContext =
		palloc0(sizeof(JoinRestrictionContext));

	plannerRestrictionContext->memoryContext = CurrentMemoryContext;

	/* we'll apply logical AND as we add tables */
	plannerRestrictionContext->relationRestrictionContext->allReferenceTables = true;

	plannerRestrictionContextList = lcons(plannerRestrictionContext,
										  plannerRestrictionContextList);

	return plannerRestrictionContext;
}