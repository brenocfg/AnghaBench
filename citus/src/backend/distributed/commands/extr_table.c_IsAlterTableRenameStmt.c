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
struct TYPE_3__ {scalar_t__ renameType; scalar_t__ relationType; } ;
typedef  TYPE_1__ RenameStmt ;

/* Variables and functions */
 scalar_t__ OBJECT_COLUMN ; 
 scalar_t__ OBJECT_FOREIGN_TABLE ; 
 scalar_t__ OBJECT_TABCONSTRAINT ; 
 scalar_t__ OBJECT_TABLE ; 

bool
IsAlterTableRenameStmt(RenameStmt *renameStmt)
{
	bool isAlterTableRenameStmt = false;

	if (renameStmt->renameType == OBJECT_TABLE ||
		renameStmt->renameType == OBJECT_FOREIGN_TABLE)
	{
		isAlterTableRenameStmt = true;
	}
	else if (renameStmt->renameType == OBJECT_COLUMN &&
			 (renameStmt->relationType == OBJECT_TABLE ||
			  renameStmt->relationType == OBJECT_FOREIGN_TABLE))
	{
		isAlterTableRenameStmt = true;
	}
	else if (renameStmt->renameType == OBJECT_TABCONSTRAINT)
	{
		isAlterTableRenameStmt = true;
	}

	return isAlterTableRenameStmt;
}