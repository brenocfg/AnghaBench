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
struct TYPE_4__ {int objectType; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterObjectDependsStmt ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
#define  OBJECT_FUNCTION 129 
#define  OBJECT_PROCEDURE 128 
 int /*<<< orphan*/ * PlanAlterFunctionDependsStmt (TYPE_1__*,char const*) ; 

__attribute__((used)) static List *
PlanAlterObjectDependsStmt(AlterObjectDependsStmt *stmt, const char *queryString)
{
	switch (stmt->objectType)
	{
		case OBJECT_PROCEDURE:
		case OBJECT_FUNCTION:
		{
			return PlanAlterFunctionDependsStmt(stmt, queryString);
		}

		default:
		{
			return NIL;
		}
	}
}