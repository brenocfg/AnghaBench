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
struct TYPE_4__ {char const* data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  AlterRoleStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AppendAlterRoleStmt (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

const char *
DeparseAlterRoleStmt(AlterRoleStmt *stmt)
{
	StringInfoData buf = { 0 };
	initStringInfo(&buf);

	AppendAlterRoleStmt(&buf, stmt);

	return buf.data;
}