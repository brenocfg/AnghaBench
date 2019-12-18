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
struct TYPE_3__ {scalar_t__ objectType; int /*<<< orphan*/  newschema; scalar_t__ object; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterObjectSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameListToQuotedString (int /*<<< orphan*/ *) ; 
 scalar_t__ OBJECT_TYPE ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppendAlterTypeSchemaStmt(StringInfo buf, AlterObjectSchemaStmt *stmt)
{
	List *names = NIL;

	Assert(stmt->objectType == OBJECT_TYPE);

	names = (List *) stmt->object;
	appendStringInfo(buf, "ALTER TYPE %s SET SCHEMA %s;", NameListToQuotedString(names),
					 quote_identifier(stmt->newschema));
}