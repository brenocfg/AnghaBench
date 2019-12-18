#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * joinRestrictionContext; TYPE_1__* relationRestrictionContext; int /*<<< orphan*/  memoryContext; } ;
struct TYPE_9__ {int allReferenceTables; int hasLocalRelation; int hasDistributedRelation; int /*<<< orphan*/  relationRestrictionList; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_1__ RelationRestrictionContext ;
typedef  int /*<<< orphan*/  Query ;
typedef  TYPE_2__ PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  JoinRestrictionContext ;

/* Variables and functions */
 int /*<<< orphan*/ * FilterJoinRestrictionContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* FilterRelationRestrictionContext (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QueryRteIdentities (int /*<<< orphan*/ *) ; 
 int ReferenceRelationCount (TYPE_1__*) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc0 (int) ; 

PlannerRestrictionContext *
FilterPlannerRestrictionForQuery(PlannerRestrictionContext *plannerRestrictionContext,
								 Query *query)
{
	PlannerRestrictionContext *filteredPlannerRestrictionContext = NULL;
	int referenceRelationCount = 0;
	int totalRelationCount = 0;

	Relids queryRteIdentities = QueryRteIdentities(query);

	RelationRestrictionContext *relationRestrictionContext =
		plannerRestrictionContext->relationRestrictionContext;
	JoinRestrictionContext *joinRestrictionContext =
		plannerRestrictionContext->joinRestrictionContext;

	RelationRestrictionContext *filteredRelationRestrictionContext =
		FilterRelationRestrictionContext(relationRestrictionContext, queryRteIdentities);

	JoinRestrictionContext *filtererdJoinRestrictionContext =
		FilterJoinRestrictionContext(joinRestrictionContext, queryRteIdentities);

	/* allocate the filtered planner restriction context and set all the fields */
	filteredPlannerRestrictionContext = palloc0(sizeof(PlannerRestrictionContext));

	filteredPlannerRestrictionContext->memoryContext =
		plannerRestrictionContext->memoryContext;

	totalRelationCount = list_length(
		filteredRelationRestrictionContext->relationRestrictionList);
	referenceRelationCount = ReferenceRelationCount(filteredRelationRestrictionContext);

	filteredRelationRestrictionContext->allReferenceTables =
		(totalRelationCount == referenceRelationCount);

	/* we currently don't support local relations and we cannot come up to this point */
	filteredRelationRestrictionContext->hasLocalRelation = false;
	filteredRelationRestrictionContext->hasDistributedRelation = true;

	/* finally set the relation and join restriction contexts */
	filteredPlannerRestrictionContext->relationRestrictionContext =
		filteredRelationRestrictionContext;
	filteredPlannerRestrictionContext->joinRestrictionContext =
		filtererdJoinRestrictionContext;

	return filteredPlannerRestrictionContext;
}