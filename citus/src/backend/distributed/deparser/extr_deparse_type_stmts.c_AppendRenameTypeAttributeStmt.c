#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ behavior; int /*<<< orphan*/  newname; int /*<<< orphan*/  subname; TYPE_1__* relation; } ;
struct TYPE_4__ {int /*<<< orphan*/  relname; int /*<<< orphan*/  schemaname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ RenameStmt ;

/* Variables and functions */
 scalar_t__ DROP_CASCADE ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_qualified_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppendRenameTypeAttributeStmt(StringInfo buf, RenameStmt *stmt)
{
	appendStringInfo(buf, "ALTER TYPE %s RENAME ATTRIBUTE %s TO %s",
					 quote_qualified_identifier(stmt->relation->schemaname,
												stmt->relation->relname),
					 quote_identifier(stmt->subname),
					 quote_identifier(stmt->newname));

	if (stmt->behavior == DROP_CASCADE)
	{
		appendStringInfoString(buf, " CASCADE");
	}

	appendStringInfoString(buf, ";");
}