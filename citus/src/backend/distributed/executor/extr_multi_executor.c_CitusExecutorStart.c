#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  planTree; } ;
struct TYPE_6__ {TYPE_2__* plannedstmt; } ;
typedef  TYPE_1__ QueryDesc ;
typedef  TYPE_2__ PlannedStmt ;

/* Variables and functions */
 scalar_t__ CitusHasBeenLoaded () ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsCitusPlan (int /*<<< orphan*/ ) ; 
 scalar_t__ IsLocalReferenceTableJoinPlan (TYPE_2__*) ; 
 scalar_t__ IsMultiStatementTransaction () ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 scalar_t__ RecoveryInProgress () ; 
 scalar_t__ WritableStandbyCoordinator ; 
 int XactReadOnly ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  standard_ExecutorStart (TYPE_1__*,int) ; 

void
CitusExecutorStart(QueryDesc *queryDesc, int eflags)
{
	PlannedStmt *plannedStmt = queryDesc->plannedstmt;

	if (CitusHasBeenLoaded())
	{
		if (IsLocalReferenceTableJoinPlan(plannedStmt) &&
			IsMultiStatementTransaction())
		{
			/*
			 * Currently we don't support this to avoid problems with tuple
			 * visibility, locking, etc. For example, change to the reference
			 * table can go through a MultiConnection, which won't be visible
			 * to the locally planned queries.
			 */
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("cannot join local tables and reference tables in "
								   "a transaction block")));
		}
	}

	/*
	 * We cannot modify XactReadOnly on Windows because it is not
	 * declared with PGDLLIMPORT.
	 */
#ifndef WIN32
	if (RecoveryInProgress() && WritableStandbyCoordinator &&
		IsCitusPlan(plannedStmt->planTree))
	{
		PG_TRY();
		{
			/*
			 * To enable writes from a hot standby we cheat our way through
			 * the checks in standard_ExecutorStart by temporarily setting
			 * XactReadOnly to false.
			 */
			XactReadOnly = false;
			standard_ExecutorStart(queryDesc, eflags);
			XactReadOnly = true;
		}
		PG_CATCH();
		{
			XactReadOnly = true;
			PG_RE_THROW();
		}
		PG_END_TRY();
	}
	else
#endif
	{
		standard_ExecutorStart(queryDesc, eflags);
	}
}