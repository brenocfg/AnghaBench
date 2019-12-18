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
struct TYPE_3__ {scalar_t__ relkind; } ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterTableStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_WORKERS ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DISABLE_DDL_PROPAGATION ; 
 char* DeparseTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  EnsureSequentialModeForTypeDDL () ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * NodeDDLTaskList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OBJECT_TYPE ; 
 int /*<<< orphan*/  QualifyTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShouldPropagateAlterType (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * list_make3 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

List *
PlanAlterTypeStmt(AlterTableStmt *stmt, const char *queryString)
{
	const char *alterTypeStmtSql = NULL;
	const ObjectAddress *typeAddress = NULL;
	List *commands = NIL;

	Assert(stmt->relkind == OBJECT_TYPE);

	typeAddress = GetObjectAddressFromParseTree((Node *) stmt, false);
	if (!ShouldPropagateAlterType(typeAddress))
	{
		return NIL;
	}

	EnsureCoordinator();

	/* reconstruct alter statement in a portable fashion */
	QualifyTreeNode((Node *) stmt);
	alterTypeStmtSql = DeparseTreeNode((Node *) stmt);

	/*
	 * all types that are distributed will need their alter statements propagated
	 * regardless if in a transaction or not. If we would not propagate the alter
	 * statement the types would be different on worker and coordinator.
	 */
	EnsureSequentialModeForTypeDDL();

	commands = list_make3(DISABLE_DDL_PROPAGATION,
						  (void *) alterTypeStmtSql,
						  ENABLE_DDL_PROPAGATION);

	return NodeDDLTaskList(ALL_WORKERS, commands);
}