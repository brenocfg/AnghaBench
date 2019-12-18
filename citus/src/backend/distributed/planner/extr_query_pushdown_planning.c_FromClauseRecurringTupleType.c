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
struct TYPE_4__ {int /*<<< orphan*/  rtable; } ;
typedef  int /*<<< orphan*/  RecurringTuplesType ;
typedef  TYPE_1__ Query ;

/* Variables and functions */
 scalar_t__ FindNodeCheckInRangeTableList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HasEmptyJoinTree (TYPE_1__*) ; 
 int /*<<< orphan*/  IsDistributedTableRTE ; 
 int /*<<< orphan*/  IsRecurringRangeTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECURRING_TUPLES_EMPTY_JOIN_TREE ; 
 int /*<<< orphan*/  RECURRING_TUPLES_INVALID ; 

__attribute__((used)) static RecurringTuplesType
FromClauseRecurringTupleType(Query *queryTree)
{
	RecurringTuplesType recurType = RECURRING_TUPLES_INVALID;

	if (HasEmptyJoinTree(queryTree))
	{
		return RECURRING_TUPLES_EMPTY_JOIN_TREE;
	}

	if (FindNodeCheckInRangeTableList(queryTree->rtable, IsDistributedTableRTE))
	{
		/*
		 * There is a distributed table somewhere in the FROM clause.
		 *
		 * In the typical case this means that the query does not recur,
		 * but there are two exceptions:
		 *
		 * - outer joins such as reference_table LEFT JOIN distributed_table
		 * - FROM reference_table WHERE .. (SELECT .. FROM distributed_table) ..
		 *
		 * However, we check all subqueries and joins separately, so we would
		 * find such conditions in other calls.
		 */
		return RECURRING_TUPLES_INVALID;
	}

	/*
	 * Try to figure out which type of recurring tuples we have to produce a
	 * relevant error message. If there are several we'll pick the first one.
	 */
	IsRecurringRangeTable(queryTree->rtable, &recurType);

	return recurType;
}