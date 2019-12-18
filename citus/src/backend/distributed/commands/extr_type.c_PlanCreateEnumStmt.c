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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  CreateEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_WORKERS ; 
 int /*<<< orphan*/  DISABLE_DDL_PROPAGATION ; 
 char* DeparseCreateEnumStmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  EnsureSequentialModeForTypeDDL () ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * NodeDDLTaskList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QualifyTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShouldPropagateTypeCreate () ; 
 char* WrapCreateOrReplace (char const*) ; 
 int /*<<< orphan*/ * list_make3 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

List *
PlanCreateEnumStmt(CreateEnumStmt *stmt, const char *queryString)
{
	const char *createEnumStmtSql = NULL;
	List *commands = NIL;

	if (!ShouldPropagateTypeCreate())
	{
		return NIL;
	}

	/*
	 * managing types can only be done on the coordinator if ddl propagation is on. when
	 * it is off we will never get here
	 */
	EnsureCoordinator();

	/* enforce fully qualified typeName for correct deparsing and lookup */
	QualifyTreeNode((Node *) stmt);

	/* reconstruct creation statement in a portable fashion */
	createEnumStmtSql = DeparseCreateEnumStmt(stmt);
	createEnumStmtSql = WrapCreateOrReplace(createEnumStmtSql);

	/*
	 * when we allow propagation within a transaction block we should make sure to only
	 * allow this in sequential mode
	 */
	EnsureSequentialModeForTypeDDL();

	/* to prevent recursion with mx we disable ddl propagation */
	commands = list_make3(DISABLE_DDL_PROPAGATION,
						  (void *) createEnumStmtSql,
						  ENABLE_DDL_PROPAGATION);

	return NodeDDLTaskList(ALL_WORKERS, commands);
}