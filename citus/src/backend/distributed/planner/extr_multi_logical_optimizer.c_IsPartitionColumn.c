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
struct TYPE_4__ {scalar_t__ varattno; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  Query ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 TYPE_1__* DistPartitionKey (scalar_t__) ; 
 int /*<<< orphan*/  FindReferencedTableColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,TYPE_1__**) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  NIL ; 

bool
IsPartitionColumn(Expr *columnExpression, Query *query)
{
	bool isPartitionColumn = false;
	Oid relationId = InvalidOid;
	Var *column = NULL;

	FindReferencedTableColumn(columnExpression, NIL, query, &relationId, &column);

	if (relationId != InvalidOid && column != NULL)
	{
		Var *partitionColumn = DistPartitionKey(relationId);

		/* not all distributed tables have partition column */
		if (partitionColumn != NULL && column->varattno == partitionColumn->varattno)
		{
			isPartitionColumn = true;
		}
	}

	return isPartitionColumn;
}