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
struct TYPE_3__ {scalar_t__ subtype; int /*<<< orphan*/  def; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ AlterTableCmd ;

/* Variables and functions */
 scalar_t__ AT_AddColumn ; 
 int /*<<< orphan*/  AppendColumnDef (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ColumnDef ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppendAlterTypeCmdAddColumn(StringInfo buf, AlterTableCmd *alterTableCmd)
{
	Assert(alterTableCmd->subtype == AT_AddColumn);

	appendStringInfoString(buf, " ADD ATTRIBUTE ");
	AppendColumnDef(buf, castNode(ColumnDef, alterTableCmd->def));
}