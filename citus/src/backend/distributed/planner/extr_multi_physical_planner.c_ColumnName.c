#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int varattno; int /*<<< orphan*/  varno; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  Value ;
struct TYPE_9__ {int /*<<< orphan*/ * colnames; } ;
struct TYPE_8__ {int /*<<< orphan*/  relid; TYPE_3__* eref; } ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  scalar_t__ CitusRTEKind ;
typedef  int AttrNumber ;
typedef  TYPE_3__ Alias ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ CITUS_RTE_RELATION ; 
 scalar_t__ CITUS_RTE_REMOTE_QUERY ; 
 scalar_t__ GetRangeTblKind (TYPE_2__*) ; 
 char* get_attname (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strVal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ColumnName(Var *column, List *rangeTableList)
{
	char *columnName = NULL;
	Index tableId = column->varno;
	AttrNumber columnNumber = column->varattno;
	RangeTblEntry *rangeTableEntry = rt_fetch(tableId, rangeTableList);

	CitusRTEKind rangeTableKind = GetRangeTblKind(rangeTableEntry);
	if (rangeTableKind == CITUS_RTE_REMOTE_QUERY)
	{
		Alias *referenceNames = rangeTableEntry->eref;
		List *columnNameList = referenceNames->colnames;
		int columnIndex = columnNumber - 1;

		Value *columnValue = (Value *) list_nth(columnNameList, columnIndex);
		columnName = strVal(columnValue);
	}
	else if (rangeTableKind == CITUS_RTE_RELATION)
	{
		Oid relationId = rangeTableEntry->relid;
		columnName = get_attname(relationId, columnNumber, false);
	}

	Assert(columnName != NULL);
	return columnName;
}