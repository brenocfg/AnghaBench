#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* sjinfo; int /*<<< orphan*/  restrictlist; } ;
struct TYPE_13__ {int /*<<< orphan*/ * outerrel; int /*<<< orphan*/ * innerrel; int /*<<< orphan*/ * plannerInfo; int /*<<< orphan*/ * joinRestrictInfoList; int /*<<< orphan*/  joinType; } ;
struct TYPE_12__ {int /*<<< orphan*/  joinRestrictionList; } ;
struct TYPE_11__ {int hasSemiJoin; TYPE_3__* joinRestrictionContext; int /*<<< orphan*/ * memoryContext; } ;
struct TYPE_10__ {scalar_t__ jointype; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_2__ PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JoinType ;
typedef  TYPE_3__ JoinRestrictionContext ;
typedef  TYPE_4__ JoinRestriction ;
typedef  TYPE_5__ JoinPathExtraData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* CurrentPlannerRestrictionContext () ; 
 scalar_t__ JOIN_SEMI ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* palloc0 (int) ; 

void
multi_join_restriction_hook(PlannerInfo *root,
							RelOptInfo *joinrel,
							RelOptInfo *outerrel,
							RelOptInfo *innerrel,
							JoinType jointype,
							JoinPathExtraData *extra)
{
	PlannerRestrictionContext *plannerRestrictionContext = NULL;
	JoinRestrictionContext *joinRestrictionContext = NULL;
	JoinRestriction *joinRestriction = NULL;
	MemoryContext restrictionsMemoryContext = NULL;
	MemoryContext oldMemoryContext = NULL;
	List *restrictInfoList = NIL;

	/*
	 * Use a memory context that's guaranteed to live long enough, could be
	 * called in a more shorted lived one (e.g. with GEQO).
	 */
	plannerRestrictionContext = CurrentPlannerRestrictionContext();
	restrictionsMemoryContext = plannerRestrictionContext->memoryContext;
	oldMemoryContext = MemoryContextSwitchTo(restrictionsMemoryContext);

	/*
	 * We create a copy of restrictInfoList because it may be created in a memory
	 * context which will be deleted when we still need it, thus we create a copy
	 * of it in our memory context.
	 */
	restrictInfoList = copyObject(extra->restrictlist);

	joinRestrictionContext = plannerRestrictionContext->joinRestrictionContext;
	Assert(joinRestrictionContext != NULL);

	joinRestriction = palloc0(sizeof(JoinRestriction));
	joinRestriction->joinType = jointype;
	joinRestriction->joinRestrictInfoList = restrictInfoList;
	joinRestriction->plannerInfo = root;
	joinRestriction->innerrel = innerrel;
	joinRestriction->outerrel = outerrel;

	joinRestrictionContext->joinRestrictionList =
		lappend(joinRestrictionContext->joinRestrictionList, joinRestriction);

	/*
	 * Keep track if we received any semi joins here. If we didn't we can
	 * later safely convert any semi joins in the rewritten query to inner
	 * joins.
	 */
	plannerRestrictionContext->hasSemiJoin = plannerRestrictionContext->hasSemiJoin ||
											 extra->sjinfo->jointype == JOIN_SEMI;

	MemoryContextSwitchTo(oldMemoryContext);
}