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
struct TYPE_4__ {int /*<<< orphan*/  objectId; } ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  CreateFunctionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_WORKERS ; 
 int /*<<< orphan*/  DISABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  ENABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  EnsureDependenciesExistsOnAllNodes (TYPE_1__ const*) ; 
 int /*<<< orphan*/  GetFunctionAlterOwnerCommand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFunctionDDLCommand (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * NodeDDLTaskList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShouldPropagateCreateFunction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

List *
ProcessCreateFunctionStmt(CreateFunctionStmt *stmt, const char *queryString)
{
	const ObjectAddress *address = NULL;
	List *commands = NIL;

	if (!ShouldPropagateCreateFunction(stmt))
	{
		return NIL;
	}

	address = GetObjectAddressFromParseTree((Node *) stmt, false);
	EnsureDependenciesExistsOnAllNodes(address);

	commands = list_make4(DISABLE_DDL_PROPAGATION,
						  GetFunctionDDLCommand(address->objectId, true),
						  GetFunctionAlterOwnerCommand(address->objectId),
						  ENABLE_DDL_PROPAGATION);

	return NodeDDLTaskList(ALL_WORKERS, commands);
}