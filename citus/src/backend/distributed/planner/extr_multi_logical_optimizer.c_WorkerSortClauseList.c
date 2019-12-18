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
struct TYPE_3__ {int canApproximate; int /*<<< orphan*/  hasOrderByAggregate; scalar_t__ groupedByDisjointPartitionColumn; scalar_t__ groupClauseIsEmpty; int /*<<< orphan*/  hasDistinctOn; } ;
typedef  TYPE_1__ OrderByLimitReference ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
WorkerSortClauseList(Node *limitCount, List *groupClauseList, List *sortClauseList,
					 OrderByLimitReference orderByLimitReference)
{
	List *workerSortClauseList = NIL;

	/* if no limit node and no hasDistinctOn, no need to push down sort clauses */
	if (limitCount == NULL && !orderByLimitReference.hasDistinctOn)
	{
		return NIL;
	}

	sortClauseList = copyObject(sortClauseList);

	/*
	 * If we are pushing down the limit, push down any order by clauses. Also if
	 * we are pushing down the limit because the order by clauses don't have any
	 * aggregates, add group by clauses to the order by list. We do this because
	 * rows that belong to the same grouping may appear in different "offsets"
	 * in different task results. By ordering on the group by clause, we ensure
	 * that query results are consistent.
	 */
	if (orderByLimitReference.groupClauseIsEmpty ||
		orderByLimitReference.groupedByDisjointPartitionColumn)
	{
		workerSortClauseList = sortClauseList;
	}
	else if (sortClauseList != NIL)
	{
		bool orderByNonAggregates = !orderByLimitReference.hasOrderByAggregate;
		bool canApproximate = orderByLimitReference.canApproximate;

		if (orderByNonAggregates)
		{
			workerSortClauseList = sortClauseList;
			workerSortClauseList = list_concat(workerSortClauseList, groupClauseList);
		}
		else if (canApproximate)
		{
			workerSortClauseList = sortClauseList;
		}
	}

	return workerSortClauseList;
}