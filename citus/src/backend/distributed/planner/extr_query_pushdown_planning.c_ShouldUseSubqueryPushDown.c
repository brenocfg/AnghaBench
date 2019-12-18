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
struct TYPE_10__ {scalar_t__ hasSemiJoin; } ;
struct TYPE_9__ {scalar_t__ hasWindowFuncs; scalar_t__ jointree; } ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  TYPE_1__ Query ;
typedef  TYPE_2__ PlannerRestrictionContext ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * DeferErrorIfUnsupportedClause (int /*<<< orphan*/ *) ; 
 scalar_t__ FindNodeCheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsFunctionRTE ; 
 int /*<<< orphan*/  IsOuterJoinExpr ; 
 scalar_t__ JoinTreeContainsSubquery (TYPE_1__*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * QualifierList (scalar_t__) ; 
 scalar_t__ SafeToPushdownWindowFunction (TYPE_1__*,int /*<<< orphan*/ **) ; 
 scalar_t__ WhereOrHavingClauseContainsSubquery (TYPE_1__*) ; 

bool
ShouldUseSubqueryPushDown(Query *originalQuery, Query *rewrittenQuery,
						  PlannerRestrictionContext *plannerRestrictionContext)
{
	List *qualifierList = NIL;
	StringInfo errorMessage = NULL;

	/*
	 * We check the existence of subqueries in FROM clause on the modified query
	 * given that if postgres already flattened the subqueries, MultiNodeTree()
	 * can plan corresponding distributed plan.
	 */
	if (JoinTreeContainsSubquery(rewrittenQuery))
	{
		return true;
	}

	/*
	 * We check the existence of subqueries in WHERE and HAVING clause on the
	 * modified query. In some cases subqueries in the original query are
	 * converted into inner joins and in those cases MultiNodeTree() can plan
	 * the rewritten plan.
	 */
	if (WhereOrHavingClauseContainsSubquery(rewrittenQuery))
	{
		return true;
	}

	/*
	 * We check if postgres planned any semi joins, MultiNodeTree doesn't
	 * support these so we fail. Postgres is able to replace some IN/ANY
	 * subqueries with semi joins and then replace those with inner joins (ones
	 * where the subquery returns unique results). This allows MultiNodeTree to
	 * execute these subqueries (because they are converted to inner joins).
	 * However, even in that case the rewrittenQuery still contains join nodes
	 * with jointype JOIN_SEMI because Postgres doesn't actually update these.
	 * The way we find out instead if it actually planned semi joins, is by
	 * checking the joins that were sent to multi_join_restriction_hook. If no
	 * joins of type JOIN_SEMI are sent it is safe to convert all JOIN_SEMI
	 * nodes to JOIN_INNER nodes (which is what is done in MultiNodeTree).
	 */
	if (plannerRestrictionContext->hasSemiJoin)
	{
		return true;
	}


	/*
	 * We process function RTEs as subqueries, since the join order planner
	 * does not know how to handle them.
	 */
	if (FindNodeCheck((Node *) originalQuery, IsFunctionRTE))
	{
		return true;
	}

	/*
	 * We handle outer joins as subqueries, since the join order planner
	 * does not know how to handle them.
	 */
	if (FindNodeCheck((Node *) originalQuery->jointree, IsOuterJoinExpr))
	{
		return true;
	}

	/*
	 * Original query may not have an outer join while rewritten query does.
	 * We should push down in this case.
	 * An example of this is https://github.com/citusdata/citus/issues/2739
	 * where postgres pulls-up the outer-join in the subquery.
	 */
	if (FindNodeCheck((Node *) rewrittenQuery->jointree, IsOuterJoinExpr))
	{
		return true;
	}

	/*
	 * Some unsupported join clauses in logical planner
	 * may be supported by subquery pushdown planner.
	 */
	qualifierList = QualifierList(rewrittenQuery->jointree);
	if (DeferErrorIfUnsupportedClause(qualifierList) != NULL)
	{
		return true;
	}

	/* check if the query has a window function and it is safe to pushdown */
	if (originalQuery->hasWindowFuncs &&
		SafeToPushdownWindowFunction(originalQuery, &errorMessage))
	{
		return true;
	}

	return false;
}