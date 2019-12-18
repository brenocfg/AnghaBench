#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int objectType; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterObjectSchemaStmt ;

/* Variables and functions */
#define  OBJECT_AGGREGATE 131 
#define  OBJECT_FUNCTION 130 
#define  OBJECT_PROCEDURE 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/ * PlanAlterFunctionSchemaStmt (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * PlanAlterTableSchemaStmt (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * PlanAlterTypeSchemaStmt (TYPE_1__*,char const*) ; 

List *
PlanAlterObjectSchemaStmt(AlterObjectSchemaStmt *stmt, const char *queryString)
{
	switch (stmt->objectType)
	{
		case OBJECT_TYPE:
		{
			return PlanAlterTypeSchemaStmt(stmt, queryString);
		}

		case OBJECT_PROCEDURE:
		case OBJECT_AGGREGATE:
		case OBJECT_FUNCTION:
		{
			return PlanAlterFunctionSchemaStmt(stmt, queryString);
		}

		default:
		{
			/* do nothing for unsupported objects */
			break;
		}
	}

	/*
	 * old behaviour, needs to be reconciled to the above switch statement for all
	 * objectType's relating to tables. Maybe it is as easy to support
	 * ALTER TABLE ... SET SCHEMA
	 */
	return PlanAlterTableSchemaStmt(stmt, queryString);
}