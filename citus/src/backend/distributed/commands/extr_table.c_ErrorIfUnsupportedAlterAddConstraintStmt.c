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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  Var ;
struct TYPE_4__ {int /*<<< orphan*/  cmds; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_1__ AlterTableStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AlterTableGetLockLevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AlterTableLookupRelation (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DistPartitionKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ErrorIfUnsupportedConstraint (int /*<<< orphan*/ ,char,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  NoLock ; 
 char PartitionMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TableColocationId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ErrorIfUnsupportedAlterAddConstraintStmt(AlterTableStmt *alterTableStatement)
{
	LOCKMODE lockmode = AlterTableGetLockLevel(alterTableStatement->cmds);
	Oid relationId = AlterTableLookupRelation(alterTableStatement, lockmode);
	char distributionMethod = PartitionMethod(relationId);
	Var *distributionColumn = DistPartitionKey(relationId);
	uint32 colocationId = TableColocationId(relationId);
	Relation relation = relation_open(relationId, ExclusiveLock);

	ErrorIfUnsupportedConstraint(relation, distributionMethod, distributionColumn,
								 colocationId);
	relation_close(relation, NoLock);
}