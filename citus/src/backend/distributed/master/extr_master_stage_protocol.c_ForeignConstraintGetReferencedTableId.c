#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ subtype; scalar_t__ def; } ;
struct TYPE_5__ {int /*<<< orphan*/  missing_ok; int /*<<< orphan*/  cmds; } ;
struct TYPE_4__ {scalar_t__ contype; int /*<<< orphan*/ * pktable; } ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Constraint ;
typedef  TYPE_2__ AlterTableStmt ;
typedef  TYPE_3__ AlterTableCmd ;

/* Variables and functions */
 scalar_t__ AT_AddConstraint ; 
 scalar_t__ CONSTR_FOREIGN ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/ * ParseTreeNode (char*) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 

Oid
ForeignConstraintGetReferencedTableId(char *queryString)
{
	Node *queryNode = ParseTreeNode(queryString);
	AlterTableStmt *foreignConstraintStmt = (AlterTableStmt *) queryNode;
	AlterTableCmd *command = (AlterTableCmd *) linitial(foreignConstraintStmt->cmds);

	if (command->subtype == AT_AddConstraint)
	{
		Constraint *constraint = (Constraint *) command->def;
		if (constraint->contype == CONSTR_FOREIGN)
		{
			RangeVar *referencedTable = constraint->pktable;

			return RangeVarGetRelid(referencedTable, NoLock,
									foreignConstraintStmt->missing_ok);
		}
	}

	return InvalidOid;
}