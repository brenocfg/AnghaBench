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
struct TYPE_3__ {scalar_t__ subtype; scalar_t__ behavior; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ AlterTableCmd ;

/* Variables and functions */
 scalar_t__ AT_DropColumn ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DROP_CASCADE ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppendAlterTypeCmdDropColumn(StringInfo buf, AlterTableCmd *alterTableCmd)
{
	Assert(alterTableCmd->subtype == AT_DropColumn);
	appendStringInfo(buf, " DROP ATTRIBUTE %s", quote_identifier(alterTableCmd->name));

	if (alterTableCmd->behavior == DROP_CASCADE)
	{
		appendStringInfoString(buf, " CASCADE");
	}
}