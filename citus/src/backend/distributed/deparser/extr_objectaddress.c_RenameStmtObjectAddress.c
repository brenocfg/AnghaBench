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
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  OBJECT_AGGREGATE 132 
#define  OBJECT_ATTRIBUTE 131 
#define  OBJECT_FUNCTION 130 
#define  OBJECT_PROCEDURE 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/  const* RenameAttributeStmtObjectAddress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  const* RenameFunctionStmtObjectAddress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  const* RenameTypeStmtObjectAddress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static const ObjectAddress *
RenameStmtObjectAddress(RenameStmt *stmt, bool missing_ok)
{
	switch (stmt->renameType)
	{
		case OBJECT_TYPE:
		{
			return RenameTypeStmtObjectAddress(stmt, missing_ok);
		}

		case OBJECT_ATTRIBUTE:
		{
			return RenameAttributeStmtObjectAddress(stmt, missing_ok);
		}

		case OBJECT_PROCEDURE:
		case OBJECT_AGGREGATE:
		case OBJECT_FUNCTION:
		{
			return RenameFunctionStmtObjectAddress(stmt, missing_ok);
		}

		default:
		{
			ereport(ERROR, (errmsg("unsupported rename statement to get object address "
								   "for")));
		}
	}
}