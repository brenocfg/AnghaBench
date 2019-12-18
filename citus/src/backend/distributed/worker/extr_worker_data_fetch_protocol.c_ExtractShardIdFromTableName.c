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
typedef  int /*<<< orphan*/  uint64 ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INVALID_SHARD_ID ; 
 int /*<<< orphan*/  SHARD_NAME_SEPARATOR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pg_strtouint64 (char*,char**,int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,int /*<<< orphan*/ ) ; 

uint64
ExtractShardIdFromTableName(const char *tableName, bool missingOk)
{
	uint64 shardId = 0;
	char *shardIdString = NULL;
	char *shardIdStringEnd = NULL;

	/* find the last underscore and increment for shardId string */
	shardIdString = strrchr(tableName, SHARD_NAME_SEPARATOR);
	if (shardIdString == NULL && !missingOk)
	{
		ereport(ERROR, (errmsg("could not extract shardId from table name \"%s\"",
							   tableName)));
	}
	else if (shardIdString == NULL && missingOk)
	{
		return INVALID_SHARD_ID;
	}

	shardIdString++;

	errno = 0;
	shardId = pg_strtouint64(shardIdString, &shardIdStringEnd, 0);

	if (errno != 0 || (*shardIdStringEnd != '\0'))
	{
		if (!missingOk)
		{
			ereport(ERROR, (errmsg("could not extract shardId from table name \"%s\"",
								   tableName)));
		}
		else
		{
			return INVALID_SHARD_ID;
		}
	}

	return shardId;
}