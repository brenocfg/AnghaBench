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
struct TYPE_3__ {int workerHasDistinctOn; int /*<<< orphan*/ * workerDistinctClause; } ;
typedef  TYPE_1__ QueryDistinctClause ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ IsGroupBySubsetOfDistinct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 

__attribute__((used)) static void
ProcessDistinctClauseForWorkerQuery(List *distinctClause, bool hasDistinctOn,
									List *groupClauseList,
									bool queryHasAggregates,
									QueryDistinctClause *queryDistinctClause,
									bool *distinctPreventsLimitPushdown)
{
	bool distinctClauseSupersetofGroupClause = false;
	bool shouldPushdownDistinct = false;

	if (distinctClause == NIL)
	{
		return;
	}

	*distinctPreventsLimitPushdown = false;

	if (groupClauseList == NIL ||
		IsGroupBySubsetOfDistinct(groupClauseList, distinctClause))
	{
		distinctClauseSupersetofGroupClause = true;
	}
	else
	{
		distinctClauseSupersetofGroupClause = false;

		/*
		 * GROUP BY being a subset of DISTINCT guarantees the
		 * distinctness on the workers. Otherwise, pushing down
		 * LIMIT might cause missing the necessary data from
		 * the worker query
		 */
		*distinctPreventsLimitPushdown = true;
	}

	/*
	 * Distinct is pushed down to worker query only if the query does not
	 * contain an aggregate in which master processing might be required to
	 * complete the final result before distinct operation. We also prevent
	 * distinct pushdown if distinct clause is missing some entries that
	 * group by clause has.
	 */
	shouldPushdownDistinct = !queryHasAggregates &&
							 distinctClauseSupersetofGroupClause;
	if (shouldPushdownDistinct)
	{
		queryDistinctClause->workerDistinctClause = distinctClause;
		queryDistinctClause->workerHasDistinctOn = hasDistinctOn;
	}
}