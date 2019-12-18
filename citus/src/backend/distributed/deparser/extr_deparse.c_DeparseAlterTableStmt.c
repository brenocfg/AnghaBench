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
struct TYPE_4__ {int relkind; } ;
typedef  TYPE_1__ AlterTableStmt ;

/* Variables and functions */
 char const* DeparseAlterTypeStmt (TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static const char *
DeparseAlterTableStmt(AlterTableStmt *stmt)
{
	switch (stmt->relkind)
	{
		case OBJECT_TYPE:
		{
			return DeparseAlterTypeStmt(stmt);
		}

		default:
		{
			ereport(ERROR, (errmsg("unsupported alter statement for deparsing")));
		}
	}
}