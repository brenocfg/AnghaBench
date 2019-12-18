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
 scalar_t__ ReadFromSecondaries ; 
 scalar_t__ RecoveryInProgress () ; 
 scalar_t__ USE_SECONDARY_NODES_ALWAYS ; 
 int /*<<< orphan*/  WritableStandbyCoordinator ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
EnsureModificationsCanRun(void)
{
	if (RecoveryInProgress() && !WritableStandbyCoordinator)
	{
		ereport(ERROR, (errmsg("writing to worker nodes is not currently allowed"),
						errdetail("the database is in recovery mode")));
	}

	if (ReadFromSecondaries == USE_SECONDARY_NODES_ALWAYS)
	{
		ereport(ERROR, (errmsg("writing to worker nodes is not currently allowed"),
						errdetail("citus.use_secondary_nodes is set to 'always'")));
	}
}