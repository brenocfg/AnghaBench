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
typedef  int /*<<< orphan*/  RenameStmt ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_WORKERS ; 
 int /*<<< orphan*/  DISABLE_DDL_PROPAGATION ; 
 char* DeparseTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  EnsureSequentialModeForTypeDDL () ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * NodeDDLTaskList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QualifyTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShouldPropagateAlterType (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * list_make3 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

List *
PlanRenameTypeStmt(RenameStmt *stmt, const char *queryString)
{
	const char *renameStmtSql = NULL;
	const ObjectAddress *typeAddress = NULL;
	List *commands = NIL;

	typeAddress = GetObjectAddressFromParseTree((Node *) stmt, false);
	if (!ShouldPropagateAlterType(typeAddress))
	{
		return NIL;
	}

	/* fully qualify */
	QualifyTreeNode((Node *) stmt);

	/* deparse sql*/
	renameStmtSql = DeparseTreeNode((Node *) stmt);

	/* to prevent recursion with mx we disable ddl propagation */
	EnsureSequentialModeForTypeDDL();

	commands = list_make3(DISABLE_DDL_PROPAGATION,
						  (void *) renameStmtSql,
						  ENABLE_DDL_PROPAGATION);

	return NodeDDLTaskList(ALL_WORKERS, commands);
}