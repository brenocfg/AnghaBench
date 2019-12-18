#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* schemaname; } ;
struct TYPE_4__ {scalar_t__ relkind; TYPE_3__* relation; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterTableStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* GetTypeNamespaceNameByNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MakeNameListFromRangeVar (TYPE_3__*) ; 
 scalar_t__ OBJECT_TYPE ; 

void
QualifyAlterTypeStmt(AlterTableStmt *stmt)
{
	Assert(stmt->relkind == OBJECT_TYPE);

	if (stmt->relation->schemaname == NULL)
	{
		List *names = MakeNameListFromRangeVar(stmt->relation);
		char *nspname = GetTypeNamespaceNameByNameList(names);
		stmt->relation->schemaname = nspname;
	}
}