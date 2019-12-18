#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int subtype; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ AlterTableCmd ;

/* Variables and functions */
#define  AT_AddColumn 130 
#define  AT_AlterColumnType 129 
#define  AT_DropColumn 128 
 int /*<<< orphan*/  AppendAlterTypeCmdAddColumn (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendAlterTypeCmdAlterColumnType (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AppendAlterTypeCmdDropColumn (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
AppendAlterTypeCmd(StringInfo buf, AlterTableCmd *alterTableCmd)
{
	switch (alterTableCmd->subtype)
	{
		case AT_AddColumn:
		{
			AppendAlterTypeCmdAddColumn(buf, alterTableCmd);
			break;
		}

		case AT_DropColumn:
		{
			AppendAlterTypeCmdDropColumn(buf, alterTableCmd);
			break;
		}

		case AT_AlterColumnType:
		{
			AppendAlterTypeCmdAlterColumnType(buf, alterTableCmd);
			break;
		}

		default:
		{
			ereport(ERROR, (errmsg("unsupported subtype for alter table command"),
							errdetail("sub command type: %d", alterTableCmd->subtype)));
		}
	}
}