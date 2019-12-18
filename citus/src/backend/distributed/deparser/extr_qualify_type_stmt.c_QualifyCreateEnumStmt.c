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
struct TYPE_3__ {int /*<<< orphan*/  typeName; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ CreateEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  QualifiedNameGetCreationNamespace (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 

void
QualifyCreateEnumStmt(CreateEnumStmt *stmt)
{
	if (list_length(stmt->typeName) == 1)
	{
		char *objname = NULL;
		Oid creationSchema = QualifiedNameGetCreationNamespace(stmt->typeName, &objname);
		stmt->typeName = list_make2(makeString(get_namespace_name(creationSchema)),
									linitial(stmt->typeName));
	}
}