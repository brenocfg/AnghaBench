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
struct TYPE_5__ {scalar_t__ newValNeighbor; scalar_t__ newValIsAfter; scalar_t__ newVal; scalar_t__ skipIfNewValExists; scalar_t__ oldVal; int /*<<< orphan*/  typeName; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ AlterEnumStmt ;

/* Variables and functions */
 scalar_t__ AlterEnumIsAddValue (TYPE_1__*) ; 
 scalar_t__ AlterEnumIsRename (TYPE_1__*) ; 
 int /*<<< orphan*/  NameListToQuotedString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 char* quote_literal_cstr (scalar_t__) ; 

__attribute__((used)) static void
AppendAlterEnumStmt(StringInfo buf, AlterEnumStmt *stmt)
{
	appendStringInfo(buf, "ALTER TYPE %s", NameListToQuotedString(stmt->typeName));

	if (AlterEnumIsRename(stmt))
	{
		/* Rename an existing label */
		appendStringInfo(buf, " RENAME VALUE %s TO %s;",
						 quote_literal_cstr(stmt->oldVal),
						 quote_literal_cstr(stmt->newVal));
	}
	else if (AlterEnumIsAddValue(stmt))
	{
		/* Add a new label */
		appendStringInfoString(buf, " ADD VALUE ");
		if (stmt->skipIfNewValExists)
		{
			appendStringInfoString(buf, "IF NOT EXISTS ");
		}
		appendStringInfoString(buf, quote_literal_cstr(stmt->newVal));

		if (stmt->newValNeighbor)
		{
			appendStringInfo(buf, " %s %s",
							 stmt->newValIsAfter ? "AFTER" : "BEFORE",
							 quote_literal_cstr(stmt->newValNeighbor));
		}

		appendStringInfoString(buf, ";");
	}
}