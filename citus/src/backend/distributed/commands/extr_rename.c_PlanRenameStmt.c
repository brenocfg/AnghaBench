#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int concurrentIndexCmd; char const* commandString; int /*<<< orphan*/  taskList; int /*<<< orphan*/  targetRelationId; } ;
struct TYPE_10__ {int renameType; int /*<<< orphan*/  missing_ok; int /*<<< orphan*/  relation; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ DDLJob ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  DDLTaskList (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ErrorIfUnsupportedRenameStmt (TYPE_1__*) ; 
 int /*<<< orphan*/  IndexGetRelation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsAlterTableRenameStmt (TYPE_1__*) ; 
 int IsDistributedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsIndexRenameStmt (TYPE_1__*) ; 
 int /*<<< orphan*/  IsPolicyRenameStmt (TYPE_1__*) ; 
 int /*<<< orphan*/ * NIL ; 
#define  OBJECT_COLUMN 133 
#define  OBJECT_FOREIGN_TABLE 132 
#define  OBJECT_INDEX 131 
#define  OBJECT_POLICY 130 
#define  OBJECT_TABCONSTRAINT 129 
#define  OBJECT_TABLE 128 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_2__*) ; 
 TYPE_2__* palloc0 (int) ; 

List *
PlanRenameStmt(RenameStmt *renameStmt, const char *renameCommand)
{
	Oid objectRelationId = InvalidOid; /* SQL Object OID */
	Oid tableRelationId = InvalidOid; /* Relation OID, maybe not the same. */
	bool isDistributedRelation = false;
	DDLJob *ddlJob = NULL;

	/*
	 * We only support some of the PostgreSQL supported RENAME statements, and
	 * our list include only renaming table and index (related) objects.
	 */
	if (!IsAlterTableRenameStmt(renameStmt) &&
		!IsIndexRenameStmt(renameStmt) &&
		!IsPolicyRenameStmt(renameStmt))
	{
		return NIL;
	}

	/*
	 * The lock levels here should be same as the ones taken in
	 * RenameRelation(), renameatt() and RenameConstraint(). However, since all
	 * three statements have identical lock levels, we just use a single statement.
	 */
	objectRelationId = RangeVarGetRelid(renameStmt->relation,
										AccessExclusiveLock,
										renameStmt->missing_ok);

	/*
	 * If the table does not exist, don't do anything here to allow PostgreSQL
	 * to throw the appropriate error or notice message later.
	 */
	if (!OidIsValid(objectRelationId))
	{
		return NIL;
	}

	/* we have no planning to do unless the table is distributed */
	switch (renameStmt->renameType)
	{
		case OBJECT_TABLE:
		case OBJECT_FOREIGN_TABLE:
		case OBJECT_COLUMN:
		case OBJECT_TABCONSTRAINT:
		case OBJECT_POLICY:
		{
			/* the target object is our tableRelationId. */
			tableRelationId = objectRelationId;
			break;
		}

		case OBJECT_INDEX:
		{
			/*
			 * here, objRelationId points to the index relation entry, and we
			 * are interested into the entry of the table on which the index is
			 * defined.
			 */
			tableRelationId = IndexGetRelation(objectRelationId, false);
			break;
		}

		default:

			/*
			 * Nodes that are not supported by Citus: we pass-through to the
			 * main PostgreSQL executor. Any Citus-supported RenameStmt
			 * renameType must appear above in the switch, explicitly.
			 */
			return NIL;
	}

	isDistributedRelation = IsDistributedTable(tableRelationId);
	if (!isDistributedRelation)
	{
		return NIL;
	}

	/*
	 * We might ERROR out on some commands, but only for Citus tables where
	 * isDistributedRelation is true. That's why this test comes this late in
	 * the function.
	 */
	ErrorIfUnsupportedRenameStmt(renameStmt);

	ddlJob = palloc0(sizeof(DDLJob));
	ddlJob->targetRelationId = tableRelationId;
	ddlJob->concurrentIndexCmd = false;
	ddlJob->commandString = renameCommand;
	ddlJob->taskList = DDLTaskList(tableRelationId, renameCommand);

	return list_make1(ddlJob);
}