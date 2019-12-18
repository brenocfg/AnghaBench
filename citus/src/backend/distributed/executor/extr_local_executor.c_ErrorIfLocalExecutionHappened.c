#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ LocalExecutionHappened ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
ErrorIfLocalExecutionHappened(void)
{
	if (LocalExecutionHappened)
	{
		ereport(ERROR, (errmsg("cannot execute command because a local execution has "
							   "already been done in the transaction"),
						errhint("Try re-running the transaction with "
								"\"SET LOCAL citus.enable_local_execution TO OFF;\""),
						errdetail("Some parallel commands cannot be executed if a "
								  "previous command has already been executed locally")));
	}
}