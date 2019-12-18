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
struct TYPE_3__ {scalar_t__ commandType; int /*<<< orphan*/ * onConflict; } ;
typedef  int /*<<< orphan*/  RowModifyLevel ;
typedef  TYPE_1__ Query ;
typedef  scalar_t__ CmdType ;

/* Variables and functions */
 scalar_t__ CMD_DELETE ; 
 scalar_t__ CMD_INSERT ; 
 scalar_t__ CMD_SELECT ; 
 scalar_t__ CMD_UPDATE ; 
 int /*<<< orphan*/  ROW_MODIFY_COMMUTATIVE ; 
 int /*<<< orphan*/  ROW_MODIFY_NONCOMMUTATIVE ; 
 int /*<<< orphan*/  ROW_MODIFY_NONE ; 
 int /*<<< orphan*/  ROW_MODIFY_READONLY ; 

RowModifyLevel
RowModifyLevelForQuery(Query *query)
{
	CmdType commandType = query->commandType;

	if (commandType == CMD_SELECT)
	{
		return ROW_MODIFY_READONLY;
	}

	if (commandType == CMD_INSERT)
	{
		if (query->onConflict == NULL)
		{
			return ROW_MODIFY_COMMUTATIVE;
		}
		else
		{
			return ROW_MODIFY_NONCOMMUTATIVE;
		}
	}

	if (commandType == CMD_UPDATE ||
		commandType == CMD_DELETE)
	{
		return ROW_MODIFY_NONCOMMUTATIVE;
	}

	return ROW_MODIFY_NONE;
}