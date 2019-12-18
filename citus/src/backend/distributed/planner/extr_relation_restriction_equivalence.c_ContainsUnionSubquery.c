#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {int /*<<< orphan*/ * setOperations; scalar_t__ jointree; int /*<<< orphan*/ * rtable; } ;
struct TYPE_7__ {scalar_t__ rtekind; TYPE_3__* subquery; } ;
struct TYPE_6__ {scalar_t__ op; } ;
typedef  TYPE_1__ SetOperationStmt ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  TYPE_3__ Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  ExtractRangeTableIndexWalker (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ RTE_SUBQUERY ; 
 scalar_t__ SETOP_UNION ; 
 int /*<<< orphan*/  linitial_int (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 TYPE_2__* rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
ContainsUnionSubquery(Query *queryTree)
{
	List *rangeTableList = queryTree->rtable;
	Node *setOperations = queryTree->setOperations;
	List *joinTreeTableIndexList = NIL;
	Index subqueryRteIndex = 0;
	uint32 joiningRangeTableCount = 0;
	RangeTblEntry *rangeTableEntry = NULL;
	Query *subqueryTree = NULL;

	ExtractRangeTableIndexWalker((Node *) queryTree->jointree, &joinTreeTableIndexList);
	joiningRangeTableCount = list_length(joinTreeTableIndexList);

	/* don't allow joins on top of unions */
	if (joiningRangeTableCount > 1)
	{
		return false;
	}

	/* subquery without FROM */
	if (joiningRangeTableCount == 0)
	{
		return false;
	}

	subqueryRteIndex = linitial_int(joinTreeTableIndexList);
	rangeTableEntry = rt_fetch(subqueryRteIndex, rangeTableList);
	if (rangeTableEntry->rtekind != RTE_SUBQUERY)
	{
		return false;
	}

	subqueryTree = rangeTableEntry->subquery;
	setOperations = subqueryTree->setOperations;
	if (setOperations != NULL)
	{
		SetOperationStmt *setOperationStatement = (SetOperationStmt *) setOperations;

		/*
		 * Note that the set operation tree is traversed elsewhere for ensuring
		 * that we only support UNIONs.
		 */
		if (setOperationStatement->op != SETOP_UNION)
		{
			return false;
		}

		return true;
	}

	return ContainsUnionSubquery(subqueryTree);
}