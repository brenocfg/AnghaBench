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
struct TYPE_6__ {int /*<<< orphan*/  join_rel_list; } ;
struct TYPE_5__ {scalar_t__ reloptkind; int /*<<< orphan*/  relids; TYPE_2__* subroot; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;

/* Variables and functions */
 scalar_t__ RELOPT_BASEREL ; 
 scalar_t__ RELOPT_JOINREL ; 
 scalar_t__ bms_num_members (int /*<<< orphan*/ ) ; 
 TYPE_1__* linitial (int /*<<< orphan*/ ) ; 
 scalar_t__ list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ShouldRecurseForRecurringTuplesJoinChecks(RelOptInfo *relOptInfo)
{
	bool shouldRecurse = true;

	/*
	 * We shouldn't recursively go down for joins since we're already
	 * going to process each join seperately. Otherwise we'd restrict
	 * the coverage. See the below sketch where (h) denotes a hash
	 * distributed relation, (r) denotes a reference table, (L) denotes
	 * LEFT JOIN and (I) denotes INNER JOIN. If we're to recurse into
	 * the inner join, we'd be preventing to push down the following
	 * join tree, which is actually safe to push down.
	 *
	 *                       (L)
	 *                      /  \
	 *                   (I)     h
	 *                  /  \
	 *                r      h
	 */
	if (relOptInfo->reloptkind == RELOPT_JOINREL)
	{
		return false;
	}

	/*
	 * Note that we treat the same query where relations appear in subqueries
	 * differently. (i.e., use SELECT * FROM r; instead of r)
	 *
	 * In that case, to relax some restrictions, we do the following optimization:
	 * If the subplan (i.e., plannerInfo corresponding to the subquery) contains any
	 * joins, we skip reference table checks keeping in mind that the join is already
	 * going to be processed seperately. This optimization should suffice for many
	 * use cases.
	 */
	if (relOptInfo->reloptkind == RELOPT_BASEREL && relOptInfo->subroot != NULL)
	{
		PlannerInfo *subroot = relOptInfo->subroot;

		if (list_length(subroot->join_rel_list) > 0)
		{
			RelOptInfo *subqueryJoin = linitial(subroot->join_rel_list);

			/*
			 * Subqueries without relations (e.g. SELECT 1) are a little funny.
			 * They are treated as having a join, but the join is between 0
			 * relations and won't be in the join restriction list and therefore
			 * won't be revisited in DeferredErrorIfUnsupportedRecurringTuplesJoin.
			 *
			 * We therefore only skip joins with >0 relations.
			 */
			if (bms_num_members(subqueryJoin->relids) > 0)
			{
				shouldRecurse = false;
			}
		}
	}

	return shouldRecurse;
}