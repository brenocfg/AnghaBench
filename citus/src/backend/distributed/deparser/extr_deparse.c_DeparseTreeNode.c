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
 int /*<<< orphan*/  AlterRoleStmt ; 
 int /*<<< orphan*/  AlterTableStmt ; 
 int /*<<< orphan*/  CompositeTypeStmt ; 
 int /*<<< orphan*/  CreateEnumStmt ; 
 char const* DeparseAlterEnumStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseAlterFunctionStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseAlterObjectDependsStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseAlterObjectSchemaStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseAlterOwnerStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseAlterRoleStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseAlterTableStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseCompositeTypeStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseCreateEnumStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseDropStmt (int /*<<< orphan*/ ) ; 
 char const* DeparseRenameStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DropStmt ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RenameStmt ; 
#define  T_AlterEnumStmt 138 
#define  T_AlterFunctionStmt 137 
#define  T_AlterObjectDependsStmt 136 
#define  T_AlterObjectSchemaStmt 135 
#define  T_AlterOwnerStmt 134 
#define  T_AlterRoleStmt 133 
#define  T_AlterTableStmt 132 
#define  T_CompositeTypeStmt 131 
#define  T_CreateEnumStmt 130 
#define  T_DropStmt 129 
#define  T_RenameStmt 128 
 int /*<<< orphan*/  castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

const char *
DeparseTreeNode(Node *stmt)
{
	switch (nodeTag(stmt))
	{
		case T_DropStmt:
		{
			return DeparseDropStmt(castNode(DropStmt, stmt));
		}

		case T_CompositeTypeStmt:
		{
			return DeparseCompositeTypeStmt(castNode(CompositeTypeStmt, stmt));
		}

		case T_CreateEnumStmt:
		{
			return DeparseCreateEnumStmt(castNode(CreateEnumStmt, stmt));
		}

		case T_AlterTableStmt:
		{
			return DeparseAlterTableStmt(castNode(AlterTableStmt, stmt));
		}

		case T_AlterEnumStmt:
		{
			return DeparseAlterEnumStmt(castNode(AlterEnumStmt, stmt));
		}

		case T_AlterFunctionStmt:
		{
			return DeparseAlterFunctionStmt(castNode(AlterFunctionStmt, stmt));
		}

		case T_RenameStmt:
		{
			return DeparseRenameStmt(castNode(RenameStmt, stmt));
		}

		case T_AlterObjectSchemaStmt:
		{
			return DeparseAlterObjectSchemaStmt(castNode(AlterObjectSchemaStmt, stmt));
		}

		case T_AlterOwnerStmt:
		{
			return DeparseAlterOwnerStmt(castNode(AlterOwnerStmt, stmt));
		}

		case T_AlterObjectDependsStmt:
		{
			return DeparseAlterObjectDependsStmt(castNode(AlterObjectDependsStmt, stmt));
		}

		case T_AlterRoleStmt:
		{
			return DeparseAlterRoleStmt(castNode(AlterRoleStmt, stmt));
		}

		default:
		{
			ereport(ERROR, (errmsg("unsupported statement for deparsing")));
		}
	}
}