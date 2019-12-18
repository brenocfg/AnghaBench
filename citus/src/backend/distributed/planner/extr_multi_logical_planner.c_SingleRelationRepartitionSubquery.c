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
struct TYPE_6__ {scalar_t__ jointree; scalar_t__ hasWindowFuncs; scalar_t__ hasSubLinks; int /*<<< orphan*/ * rtable; } ;
struct TYPE_5__ {scalar_t__ rtekind; TYPE_2__* subquery; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ExtractRangeTableIndexWalker (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ RTE_RELATION ; 
 scalar_t__ RTE_SUBQUERY ; 
 int linitial_int (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 TYPE_1__* rt_fetch (int,int /*<<< orphan*/ *) ; 

bool
SingleRelationRepartitionSubquery(Query *queryTree)
{
	List *rangeTableIndexList = NULL;
	RangeTblEntry *rangeTableEntry = NULL;
	List *rangeTableList = queryTree->rtable;
	int rangeTableIndex = 0;

	/* we don't support subqueries in WHERE */
	if (queryTree->hasSubLinks)
	{
		return false;
	}

	/* we don't support window functions */
	if (queryTree->hasWindowFuncs)
	{
		return false;
	}

	/*
	 * Don't allow joins and set operations. If join appears in the queryTree, the
	 * length would be greater than 1. If only set operations exists, the length
	 * would be 0.
	 */
	ExtractRangeTableIndexWalker((Node *) queryTree->jointree,
								 &rangeTableIndexList);
	if (list_length(rangeTableIndexList) != 1)
	{
		return false;
	}

	rangeTableIndex = linitial_int(rangeTableIndexList);
	rangeTableEntry = rt_fetch(rangeTableIndex, rangeTableList);
	if (rangeTableEntry->rtekind == RTE_RELATION)
	{
		return true;
	}
	else if (rangeTableEntry->rtekind == RTE_SUBQUERY)
	{
		Query *subqueryTree = rangeTableEntry->subquery;

		return SingleRelationRepartitionSubquery(subqueryTree);
	}

	return false;
}