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
struct TYPE_3__ {scalar_t__ renameType; int /*<<< orphan*/ * object; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* GetTypeNamespaceNameByNameList (int /*<<< orphan*/ *) ; 
 scalar_t__ OBJECT_TYPE ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 

void
QualifyRenameTypeStmt(RenameStmt *stmt)
{
	List *names = (List *) stmt->object;

	Assert(stmt->renameType == OBJECT_TYPE);

	if (list_length(names) == 1)
	{
		/* not qualified, lookup name and add namespace name to names */
		char *nspname = GetTypeNamespaceNameByNameList(names);
		names = list_make2(makeString(nspname), linitial(names));

		stmt->object = (Node *) names;
	}
}