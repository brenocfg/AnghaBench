#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * quals; } ;
struct TYPE_4__ {int /*<<< orphan*/  rtable; TYPE_2__* jointree; } ;
typedef  TYPE_1__ Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ FromExpr ;

/* Variables and functions */
 scalar_t__ FindNodeCheckInRangeTableList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsDistributedTableRTE ; 

__attribute__((used)) static bool
ShouldRecursivelyPlanAllSubqueriesInWhere(Query *query)
{
	FromExpr *joinTree = NULL;
	Node *whereClause = NULL;

	joinTree = query->jointree;
	if (joinTree == NULL)
	{
		/* there is no FROM clause */
		return false;
	}

	whereClause = joinTree->quals;
	if (whereClause == NULL)
	{
		/* there is no WHERE clause */
		return false;
	}

	if (FindNodeCheckInRangeTableList(query->rtable, IsDistributedTableRTE))
	{
		/* there is a distributed table in the FROM clause */
		return false;
	}

	return true;
}