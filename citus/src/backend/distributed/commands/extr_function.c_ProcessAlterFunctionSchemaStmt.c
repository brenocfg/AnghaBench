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
struct TYPE_3__ {int /*<<< orphan*/  objectType; } ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ AlterObjectSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AssertObjectTypeIsFunctional (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnsureDependenciesExistsOnAllNodes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ShouldPropagateAlterFunction (int /*<<< orphan*/  const*) ; 

void
ProcessAlterFunctionSchemaStmt(AlterObjectSchemaStmt *stmt, const char *queryString)
{
	const ObjectAddress *address = NULL;

	AssertObjectTypeIsFunctional(stmt->objectType);

	address = GetObjectAddressFromParseTree((Node *) stmt, false);
	if (!ShouldPropagateAlterFunction(address))
	{
		return;
	}

	/* dependencies have changed (schema) lets ensure they exist */
	EnsureDependenciesExistsOnAllNodes(address);
}