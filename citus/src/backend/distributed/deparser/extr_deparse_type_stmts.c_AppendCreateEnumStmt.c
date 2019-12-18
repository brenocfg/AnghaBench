#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vals; int /*<<< orphan*/  typeName; } ;
struct TYPE_5__ {int /*<<< orphan*/  relname; int /*<<< orphan*/  schemaname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ RangeVar ;
typedef  TYPE_2__ CreateEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AppendStringList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* makeRangeVarFromNameList (int /*<<< orphan*/ ) ; 
 char* quote_qualified_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppendCreateEnumStmt(StringInfo str, CreateEnumStmt *stmt)
{
	RangeVar *typevar = NULL;
	const char *identifier = NULL;

	typevar = makeRangeVarFromNameList(stmt->typeName);

	/* create the identifier from the fully qualified rangevar */
	identifier = quote_qualified_identifier(typevar->schemaname, typevar->relname);

	appendStringInfo(str, "CREATE TYPE %s AS ENUM (", identifier);
	AppendStringList(str, stmt->vals);
	appendStringInfo(str, ");");
}