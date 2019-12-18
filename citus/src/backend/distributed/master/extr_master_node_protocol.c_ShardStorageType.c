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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int CStoreTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 char RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RegularTable (int /*<<< orphan*/ ) ; 
 char SHARD_STORAGE_COLUMNAR ; 
 char SHARD_STORAGE_FOREIGN ; 
 char SHARD_STORAGE_TABLE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 

char
ShardStorageType(Oid relationId)
{
	char shardStorageType = 0;

	char relationType = get_rel_relkind(relationId);
	if (RegularTable(relationId))
	{
		shardStorageType = SHARD_STORAGE_TABLE;
	}
	else if (relationType == RELKIND_FOREIGN_TABLE)
	{
		bool cstoreTable = CStoreTable(relationId);
		if (cstoreTable)
		{
			shardStorageType = SHARD_STORAGE_COLUMNAR;
		}
		else
		{
			shardStorageType = SHARD_STORAGE_FOREIGN;
		}
	}
	else
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("unexpected relation type: %c", relationType)));
	}

	return shardStorageType;
}