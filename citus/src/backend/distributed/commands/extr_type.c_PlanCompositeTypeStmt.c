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
typedef  int /*<<< orphan*/  CompositeTypeStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_WORKERS ; 
 int /*<<< orphan*/  DISABLE_DDL_PROPAGATION ; 
 char* DeparseCompositeTypeStmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/  ENABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  EnsureSequentialModeForTypeDDL () ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * NodeDDLTaskList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QualifyTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowShareLock ; 
 int /*<<< orphan*/  ShouldPropagateTypeCreate () ; 
 char* WrapCreateOrReplace (char const*) ; 
 int /*<<< orphan*/ * list_make3 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

List *
PlanCompositeTypeStmt(CompositeTypeStmt *stmt, const char *queryString)
{
	const char *compositeTypeStmtSql = NULL;
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

	/*
	 * Make sure that no new nodes are added after this point until the end of the
	 * transaction by taking a RowShareLock on pg_dist_node, which conflicts with the
	 * ExclusiveLock taken by master_add_node.
	 * This guarantees that all active nodes will have the object, because they will
	 * either get it now, or get it in master_add_node after this transaction finishes and
	 * the pg_dist_object record becomes visible.
	 */
	LockRelationOid(DistNodeRelationId(), RowShareLock);

	/* fully qualify before lookup and later deparsing */
	QualifyTreeNode((Node *) stmt);

	/*
	 * reconstruct creation statement in a portable fashion. The create_or_replace helper
	 * function will be used to create the type in an idempotent manner on the workers.
	 *
	 * Types could exist on the worker prior to being created on the coordinator when the
	 * type previously has been attempted to be created in a transaction which did not
	 * commit on the coordinator.
	 */
	compositeTypeStmtSql = DeparseCompositeTypeStmt(stmt);
	compositeTypeStmtSql = WrapCreateOrReplace(compositeTypeStmtSql);

	/*
	 * when we allow propagation within a transaction block we should make sure to only
	 * allow this in sequential mode
	 */
	EnsureSequentialModeForTypeDDL();

	commands = list_make3(DISABLE_DDL_PROPAGATION,
						  (void *) compositeTypeStmtSql,
						  ENABLE_DDL_PROPAGATION);

	return NodeDDLTaskList(ALL_WORKERS, commands);
}