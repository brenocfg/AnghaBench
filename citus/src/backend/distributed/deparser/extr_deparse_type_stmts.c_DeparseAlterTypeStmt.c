#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ relkind; } ;
struct TYPE_7__ {char const* data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ AlterTableStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AppendAlterTypeStmt (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ OBJECT_TYPE ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

const char *
DeparseAlterTypeStmt(AlterTableStmt *stmt)
{
	StringInfoData str = { 0 };
	initStringInfo(&str);

	Assert(stmt->relkind == OBJECT_TYPE);

	AppendAlterTypeStmt(&str, stmt);

	return str.data;
}