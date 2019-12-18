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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 char REPLICATION_MODEL_STREAMING ; 
 int ShardReplicationFactor ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 

void
EnsureReplicationSettings(Oid relationId, char replicationModel)
{
	char *msgSuffix = "the streaming replication model";
	char *extraHint = " or setting \"citus.replication_model\" to \"statement\"";

	if (relationId != InvalidOid)
	{
		msgSuffix = "tables which use the streaming replication model";
		extraHint = "";
	}

	if (replicationModel == REPLICATION_MODEL_STREAMING && ShardReplicationFactor != 1)
	{
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("replication factors above one are incompatible with %s",
							   msgSuffix),
						errhint("Try again after reducing \"citus.shard_replication_"
								"factor\" to one%s.", extraHint)));
	}
}