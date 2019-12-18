#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int renameType; } ;
typedef  TYPE_1__ RenameStmt ;

/* Variables and functions */
 char const* DeparseRenameAttributeStmt (TYPE_1__*) ; 
 char const* DeparseRenameFunctionStmt (TYPE_1__*) ; 
 char const* DeparseRenameTypeStmt (TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
#define  OBJECT_AGGREGATE 132 
#define  OBJECT_ATTRIBUTE 131 
#define  OBJECT_FUNCTION 130 
#define  OBJECT_PROCEDURE 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static const char *
DeparseRenameStmt(RenameStmt *stmt)
{
	switch (stmt->renameType)
	{
		case OBJECT_TYPE:
		{
			return DeparseRenameTypeStmt(stmt);
		}

		case OBJECT_ATTRIBUTE:
		{
			return DeparseRenameAttributeStmt(stmt);
		}

		case OBJECT_PROCEDURE:
		case OBJECT_AGGREGATE:
		case OBJECT_FUNCTION:
		{
			return DeparseRenameFunctionStmt(stmt);
		}

		default:
		{
			ereport(ERROR, (errmsg("unsupported rename statement for deparsing")));
		}
	}
}