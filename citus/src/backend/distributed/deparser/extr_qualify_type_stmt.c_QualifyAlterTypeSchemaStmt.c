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
struct TYPE_3__ {scalar_t__ objectType; int /*<<< orphan*/ * object; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterObjectSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* GetTypeNamespaceNameByNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ OBJECT_TYPE ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 

void
QualifyAlterTypeSchemaStmt(AlterObjectSchemaStmt *stmt)
{
	List *names = NIL;

	Assert(stmt->objectType == OBJECT_TYPE);

	names = (List *) stmt->object;
	if (list_length(names) == 1)
	{
		/* not qualified with schema, lookup type and its schema s*/
		char *nspname = GetTypeNamespaceNameByNameList(names);
		names = list_make2(makeString(nspname), linitial(names));
		stmt->object = (Node *) names;
	}
}