#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int objectType; } ;
typedef  TYPE_1__ AlterOwnerStmt ;

/* Variables and functions */
#define  OBJECT_FUNCTION 130 
#define  OBJECT_PROCEDURE 129 
#define  OBJECT_TYPE 128 
 int /*<<< orphan*/  QualifyAlterFunctionOwnerStmt (TYPE_1__*) ; 
 int /*<<< orphan*/  QualifyAlterTypeOwnerStmt (TYPE_1__*) ; 

__attribute__((used)) static void
QualifyAlterOwnerStmt(AlterOwnerStmt *stmt)
{
	switch (stmt->objectType)
	{
		case OBJECT_TYPE:
		{
			QualifyAlterTypeOwnerStmt(stmt);
			return;
		}

		case OBJECT_FUNCTION:
		case OBJECT_PROCEDURE:
		{
			QualifyAlterFunctionOwnerStmt(stmt);
		}

		default:
		{
			return;
		}
	}
}