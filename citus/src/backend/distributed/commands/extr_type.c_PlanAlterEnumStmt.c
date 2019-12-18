#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  AlterEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_WORKERS ; 
 scalar_t__ AlterEnumIsAddValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DISABLE_DDL_PROPAGATION ; 
 char* DeparseTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  EnsureSequentialModeForTypeDDL () ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * NodeDDLTaskList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QualifyTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShouldPropagateAlterType (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * list_make3 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

List *
PlanAlterEnumStmt(AlterEnumStmt *stmt, const char *queryString)
{
	const char *alterEnumStmtSql = NULL;
	const ObjectAddress *typeAddress = NULL;
	List *commands = NIL;

	typeAddress = GetObjectAddressFromParseTree((Node *) stmt, false);
	if (!ShouldPropagateAlterType(typeAddress))
	{
		return NIL;
	}

	/*
	 * alter enum will run for all distributed enums, regardless if in a transaction or
	 * not since the enum will be different on the coordinator and workers if we didn't.
	 * (adding values to an enum can not run in a transaction anyway and would error by
	 * postgres already).
	 */
	EnsureSequentialModeForTypeDDL();

	/*
	 * managing types can only be done on the coordinator if ddl propagation is on. when
	 * it is off we will never get here
	 */
	EnsureCoordinator();

	QualifyTreeNode((Node *) stmt);
	alterEnumStmtSql = DeparseTreeNode((Node *) stmt);

	/*
	 * Before pg12 ALTER ENUM ... ADD VALUE could not be within a xact block. Instead of
	 * creating a DDLTaksList we won't return anything here. During the processing phase
	 * we directly connect to workers and execute the commands remotely.
	 */
#if PG_VERSION_NUM < 120000
	if (AlterEnumIsAddValue(stmt))
	{
		/*
		 * a plan cannot be made as it will be committed via 2PC when ran through the
		 * executor, instead we directly distributed during processing phase
		 */
		return NIL;
	}
#endif

	commands = list_make3(DISABLE_DDL_PROPAGATION,
						  (void *) alterEnumStmtSql,
						  ENABLE_DDL_PROPAGATION);

	return NodeDDLTaskList(ALL_WORKERS, commands);
}