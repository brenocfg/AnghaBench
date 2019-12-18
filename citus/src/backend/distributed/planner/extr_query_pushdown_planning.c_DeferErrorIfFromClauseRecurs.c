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
struct TYPE_4__ {int /*<<< orphan*/  hasSubLinks; } ;
typedef  scalar_t__ RecurringTuplesType ;
typedef  TYPE_1__ Query ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;

/* Variables and functions */
 int /*<<< orphan*/ * DeferredError (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 scalar_t__ FromClauseRecurringTupleType (TYPE_1__*) ; 
 scalar_t__ RECURRING_TUPLES_EMPTY_JOIN_TREE ; 
 scalar_t__ RECURRING_TUPLES_FUNCTION ; 
 scalar_t__ RECURRING_TUPLES_INVALID ; 
 scalar_t__ RECURRING_TUPLES_REFERENCE_TABLE ; 
 scalar_t__ RECURRING_TUPLES_RESULT_FUNCTION ; 

__attribute__((used)) static DeferredErrorMessage *
DeferErrorIfFromClauseRecurs(Query *queryTree)
{
	RecurringTuplesType recurType = RECURRING_TUPLES_INVALID;

	if (!queryTree->hasSubLinks)
	{
		return NULL;
	}

	recurType = FromClauseRecurringTupleType(queryTree);
	if (recurType == RECURRING_TUPLES_REFERENCE_TABLE)
	{
		return DeferredError(ERRCODE_FEATURE_NOT_SUPPORTED,
							 "cannot pushdown the subquery",
							 "Reference tables are not allowed in FROM "
							 "clause when the query has subqueries in "
							 "WHERE clause and it references a column "
							 "from another query", NULL);
	}
	else if (recurType == RECURRING_TUPLES_FUNCTION)
	{
		return DeferredError(ERRCODE_FEATURE_NOT_SUPPORTED,
							 "cannot pushdown the subquery",
							 "Functions are not allowed in FROM "
							 "clause when the query has subqueries in "
							 "WHERE clause and it references a column "
							 "from another query", NULL);
	}
	else if (recurType == RECURRING_TUPLES_RESULT_FUNCTION)
	{
		return DeferredError(ERRCODE_FEATURE_NOT_SUPPORTED,
							 "cannot pushdown the subquery",
							 "Complex subqueries and CTEs are not allowed in "
							 "the FROM clause when the query has subqueries in the "
							 "WHERE clause and it references a column "
							 "from another query", NULL);
	}
	else if (recurType == RECURRING_TUPLES_EMPTY_JOIN_TREE)
	{
		return DeferredError(ERRCODE_FEATURE_NOT_SUPPORTED,
							 "cannot pushdown the subquery",
							 "Subqueries without FROM are not allowed in FROM "
							 "clause when the outer query has subqueries in "
							 "WHERE clause and it references a column "
							 "from another query", NULL);
	}

	/*
	 * We get here when there is neither a distributed table, nor recurring tuples.
	 * That usually means that there isn't a FROM at all (only sublinks), this
	 * implies that queryTree is recurring, but whether this is a problem depends
	 * on outer queries, not on queryTree itself.
	 */

	return NULL;
}