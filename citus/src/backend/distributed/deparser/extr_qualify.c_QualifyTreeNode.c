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

/* Variables and functions */
 int /*<<< orphan*/  AlterEnumStmt ; 
 int /*<<< orphan*/  AlterFunctionStmt ; 
 int /*<<< orphan*/  AlterObjectDependsStmt ; 
 int /*<<< orphan*/  AlterObjectSchemaStmt ; 
 int /*<<< orphan*/  AlterOwnerStmt ; 
 int /*<<< orphan*/  AlterTableStmt ; 
 int /*<<< orphan*/  CompositeTypeStmt ; 
 int /*<<< orphan*/  CreateEnumStmt ; 
 int /*<<< orphan*/  QualifyAlterEnumStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QualifyAlterFunctionStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QualifyAlterObjectDependsStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QualifyAlterObjectSchemaStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QualifyAlterOwnerStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QualifyAlterTableStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QualifyCompositeTypeStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QualifyCreateEnumStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QualifyRenameStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RenameStmt ; 
#define  T_AlterEnumStmt 136 
#define  T_AlterFunctionStmt 135 
#define  T_AlterObjectDependsStmt 134 
#define  T_AlterObjectSchemaStmt 133 
#define  T_AlterOwnerStmt 132 
#define  T_AlterTableStmt 131 
#define  T_CompositeTypeStmt 130 
#define  T_CreateEnumStmt 129 
#define  T_RenameStmt 128 
 int /*<<< orphan*/  castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

void
QualifyTreeNode(Node *stmt)
{
	switch (nodeTag(stmt))
	{
		case T_RenameStmt:
		{
			QualifyRenameStmt(castNode(RenameStmt, stmt));
			return;
		}

		case T_AlterEnumStmt:
		{
			QualifyAlterEnumStmt(castNode(AlterEnumStmt, stmt));
			return;
		}

		case T_AlterTableStmt:
		{
			QualifyAlterTableStmt(castNode(AlterTableStmt, stmt));
			return;
		}

		case T_CompositeTypeStmt:
		{
			QualifyCompositeTypeStmt(castNode(CompositeTypeStmt, stmt));
			return;
		}

		case T_CreateEnumStmt:
		{
			QualifyCreateEnumStmt(castNode(CreateEnumStmt, stmt));
			return;
		}

		case T_AlterObjectSchemaStmt:
		{
			QualifyAlterObjectSchemaStmt(castNode(AlterObjectSchemaStmt, stmt));
			return;
		}

		case T_AlterOwnerStmt:
		{
			QualifyAlterOwnerStmt(castNode(AlterOwnerStmt, stmt));
			return;
		}

		case T_AlterFunctionStmt:
		{
			QualifyAlterFunctionStmt(castNode(AlterFunctionStmt, stmt));
			return;
		}

		case T_AlterObjectDependsStmt:
		{
			QualifyAlterObjectDependsStmt(castNode(AlterObjectDependsStmt, stmt));
			return;
		}

		default:
		{
			/* skip unsupported statements */
			break;
		}
	}
}