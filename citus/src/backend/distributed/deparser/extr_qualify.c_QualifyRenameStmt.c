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
#define  OBJECT_ATTRIBUTE 131 
#define  OBJECT_FUNCTION 130 
#define  OBJECT_PROCEDURE 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/  QualifyRenameAttributeStmt (TYPE_1__*) ; 
 int /*<<< orphan*/  QualifyRenameFunctionStmt (TYPE_1__*) ; 
 int /*<<< orphan*/  QualifyRenameTypeStmt (TYPE_1__*) ; 

__attribute__((used)) static void
QualifyRenameStmt(RenameStmt *stmt)
{
	switch (stmt->renameType)
	{
		case OBJECT_TYPE:
		{
			QualifyRenameTypeStmt(stmt);
			return;
		}

		case OBJECT_ATTRIBUTE:
		{
			QualifyRenameAttributeStmt(stmt);
			return;
		}

		case OBJECT_FUNCTION:
		case OBJECT_PROCEDURE:
		{
			QualifyRenameFunctionStmt(stmt);
		}

		default:
		{
			/* skip unsupported statements */
			break;
		}
	}
}