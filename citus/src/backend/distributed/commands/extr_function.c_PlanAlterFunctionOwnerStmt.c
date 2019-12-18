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
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterOwnerStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_WORKERS ; 
 int /*<<< orphan*/  AssertObjectTypeIsFunctional (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISABLE_DDL_PROPAGATION ; 
 char* DeparseTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  EnsureSequentialModeForFunctionDDL () ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * NodeDDLTaskList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QualifyTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShouldPropagateAlterFunction (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * list_make3 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

List *
PlanAlterFunctionOwnerStmt(AlterOwnerStmt *stmt, const char *queryString)
{
	const ObjectAddress *address = NULL;
	const char *sql = NULL;
	List *commands = NULL;

	AssertObjectTypeIsFunctional(stmt->objectType);

	address = GetObjectAddressFromParseTree((Node *) stmt, false);
	if (!ShouldPropagateAlterFunction(address))
	{
		return NIL;
	}

	EnsureCoordinator();
	EnsureSequentialModeForFunctionDDL();
	QualifyTreeNode((Node *) stmt);
	sql = DeparseTreeNode((Node *) stmt);

	commands = list_make3(DISABLE_DDL_PROPAGATION,
						  (void *) sql,
						  ENABLE_DDL_PROPAGATION);

	return NodeDDLTaskList(ALL_WORKERS, commands);
}