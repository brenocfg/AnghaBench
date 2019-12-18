#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  targetlist; } ;
typedef  TYPE_1__ Plan ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  AttrNumber ;
typedef  int /*<<< orphan*/  AggStrategy ;
typedef  int /*<<< orphan*/  Agg ;

/* Variables and functions */
 int /*<<< orphan*/  AGGSPLIT_SIMPLE ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  extract_grouping_collations (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extract_grouping_cols (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extract_grouping_ops (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_agg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,...) ; 

__attribute__((used)) static Agg *
makeAggNode(List *groupClauseList, List *havingQual, AggStrategy aggrStrategy,
			List *queryTargetList, Plan *subPlan)
{
	Agg *aggNode = NULL;
	int groupColumnCount = list_length(groupClauseList);
	AttrNumber *groupColumnIdArray =
		extract_grouping_cols(groupClauseList, subPlan->targetlist);
	Oid *groupColumnOpArray = extract_grouping_ops(groupClauseList);
	const int rowEstimate = 10;

#if (PG_VERSION_NUM >= 120000)
	aggNode = make_agg(queryTargetList, havingQual, aggrStrategy,
					   AGGSPLIT_SIMPLE, groupColumnCount, groupColumnIdArray,
					   groupColumnOpArray,
					   extract_grouping_collations(groupClauseList,
												   subPlan->targetlist),
					   NIL, NIL, rowEstimate, subPlan);
#else
	aggNode = make_agg(queryTargetList, havingQual, aggrStrategy,
					   AGGSPLIT_SIMPLE, groupColumnCount, groupColumnIdArray,
					   groupColumnOpArray,
					   NIL, NIL, rowEstimate, subPlan);
#endif

	return aggNode;
}