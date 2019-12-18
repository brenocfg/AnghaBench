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
struct TYPE_5__ {scalar_t__ renameType; scalar_t__ relationType; TYPE_1__* relation; } ;
struct TYPE_4__ {char* schemaname; int /*<<< orphan*/  relname; } ;
typedef  TYPE_2__ RenameStmt ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* GetTypeNamespaceNameByNameList (int /*<<< orphan*/ *) ; 
 scalar_t__ OBJECT_ATTRIBUTE ; 
 scalar_t__ OBJECT_TYPE ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 

void
QualifyRenameTypeAttributeStmt(RenameStmt *stmt)
{
	Assert(stmt->renameType == OBJECT_ATTRIBUTE);
	Assert(stmt->relationType == OBJECT_TYPE);

	if (stmt->relation->schemaname == NULL)
	{
		List *names = list_make1(makeString(stmt->relation->relname));
		char *nspname = GetTypeNamespaceNameByNameList(names);
		stmt->relation->schemaname = nspname;
	}
}