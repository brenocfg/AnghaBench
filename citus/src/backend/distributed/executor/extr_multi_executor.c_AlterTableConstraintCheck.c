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
struct TYPE_5__ {TYPE_1__* plannedstmt; } ;
struct TYPE_4__ {scalar_t__ commandType; int /*<<< orphan*/  planTree; } ;
typedef  TYPE_2__ QueryDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AlterTableInProgress () ; 
 scalar_t__ CMD_SELECT ; 
 int /*<<< orphan*/  IsCitusPlan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
AlterTableConstraintCheck(QueryDesc *queryDesc)
{
	if (!AlterTableInProgress())
	{
		return false;
	}

	/*
	 * These queries are one or more SELECT queries, where postgres checks
	 * their results either for NULL values or existence of a row at all.
	 */
	if (queryDesc->plannedstmt->commandType != CMD_SELECT)
	{
		return false;
	}

	/*
	 * While an ALTER TABLE is in progress, we might do SELECTs on some
	 * catalog tables too. For example, when dropping a column, citus_drop_trigger()
	 * runs some SELECTs on catalog tables. These are not constraint check queries.
	 */
	if (!IsCitusPlan(queryDesc->plannedstmt->planTree))
	{
		return false;
	}

	return true;
}