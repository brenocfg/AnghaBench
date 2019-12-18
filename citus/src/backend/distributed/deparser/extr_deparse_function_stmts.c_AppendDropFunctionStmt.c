#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ behavior; int /*<<< orphan*/  removeType; int /*<<< orphan*/  objects; scalar_t__ missing_ok; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ DropStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AppendFunctionNameList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DROP_CASCADE ; 
 int /*<<< orphan*/  ObjectTypeToKeyword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
AppendDropFunctionStmt(StringInfo buf, DropStmt *stmt)
{
	appendStringInfo(buf, "DROP %s ", ObjectTypeToKeyword(stmt->removeType));

	if (stmt->missing_ok)
	{
		appendStringInfoString(buf, "IF EXISTS ");
	}

	AppendFunctionNameList(buf, stmt->objects, stmt->removeType);

	if (stmt->behavior == DROP_CASCADE)
	{
		appendStringInfoString(buf, " CASCADE");
	}

	appendStringInfoString(buf, ";");
}