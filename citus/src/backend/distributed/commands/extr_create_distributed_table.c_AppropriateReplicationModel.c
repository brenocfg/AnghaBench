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
 char DISTRIBUTE_BY_HASH ; 
 char DISTRIBUTE_BY_NONE ; 
 int /*<<< orphan*/  NOTICE ; 
 char REPLICATION_MODEL_2PC ; 
 scalar_t__ REPLICATION_MODEL_COORDINATOR ; 
 char REPLICATION_MODEL_INVALID ; 
 scalar_t__ ReplicationModel ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static char
AppropriateReplicationModel(char distributionMethod, bool viaDeprecatedAPI)
{
	if (viaDeprecatedAPI)
	{
		if (ReplicationModel != REPLICATION_MODEL_COORDINATOR)
		{
			ereport(NOTICE, (errmsg("using statement-based replication"),
							 errdetail("The current replication_model setting is "
									   "'streaming', which is not supported by "
									   "master_create_distributed_table."),
							 errhint("Use create_distributed_table to use the streaming "
									 "replication model.")));
		}

		return REPLICATION_MODEL_COORDINATOR;
	}
	else if (distributionMethod == DISTRIBUTE_BY_NONE)
	{
		return REPLICATION_MODEL_2PC;
	}
	else if (distributionMethod == DISTRIBUTE_BY_HASH)
	{
		return ReplicationModel;
	}
	else
	{
		if (ReplicationModel != REPLICATION_MODEL_COORDINATOR)
		{
			ereport(NOTICE, (errmsg("using statement-based replication"),
							 errdetail("Streaming replication is supported only for "
									   "hash-distributed tables.")));
		}

		return REPLICATION_MODEL_COORDINATOR;
	}

	/* we should not reach to this point */
	return REPLICATION_MODEL_INVALID;
}