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
struct TYPE_3__ {int /*<<< orphan*/  varattno; int /*<<< orphan*/  varno; int /*<<< orphan*/  varoattno; int /*<<< orphan*/  varnoold; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 scalar_t__ CITUS_RTE_REMOTE_QUERY ; 
 scalar_t__ GetRangeTblKind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewColumnId (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewTableId (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
UpdateColumnAttributes(Var *column, List *rangeTableList, List *dependedJobList)
{
	Index originalTableId = column->varnoold;
	AttrNumber originalColumnId = column->varoattno;

	/* find the new table identifier */
	Index newTableId = NewTableId(originalTableId, rangeTableList);
	AttrNumber newColumnId = originalColumnId;

	/* if this is a derived table, find the new column identifier */
	RangeTblEntry *newRangeTableEntry = rt_fetch(newTableId, rangeTableList);
	if (GetRangeTblKind(newRangeTableEntry) == CITUS_RTE_REMOTE_QUERY)
	{
		newColumnId = NewColumnId(originalTableId, originalColumnId,
								  newRangeTableEntry, dependedJobList);
	}

	column->varno = newTableId;
	column->varattno = newColumnId;
}