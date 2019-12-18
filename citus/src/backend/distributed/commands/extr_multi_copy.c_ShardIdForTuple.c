#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_6__ {int partitionColumnIndex; int /*<<< orphan*/  tableMetadata; int /*<<< orphan*/  distributedRelationId; int /*<<< orphan*/ * columnCoercionPaths; } ;
struct TYPE_5__ {int /*<<< orphan*/  shardId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  CopyCoercionData ;
typedef  TYPE_2__ CitusCopyDestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  CoerceColumnValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* FindShardInterval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INVALID_PARTITION_COLUMN_INDEX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 char* quote_qualified_identifier (char*,char*) ; 

__attribute__((used)) static uint64
ShardIdForTuple(CitusCopyDestReceiver *copyDest, Datum *columnValues, bool *columnNulls)
{
	int partitionColumnIndex = copyDest->partitionColumnIndex;
	Datum partitionColumnValue = 0;
	CopyCoercionData *columnCoercionPaths = copyDest->columnCoercionPaths;
	ShardInterval *shardInterval = NULL;

	/*
	 * Find the partition column value and corresponding shard interval
	 * for non-reference tables.
	 * Get the existing (and only a single) shard interval for the reference
	 * tables. Note that, reference tables has NULL partition column values so
	 * skip the check.
	 */
	if (partitionColumnIndex != INVALID_PARTITION_COLUMN_INDEX)
	{
		CopyCoercionData *coercePath = &columnCoercionPaths[partitionColumnIndex];

		if (columnNulls[partitionColumnIndex])
		{
			Oid relationId = copyDest->distributedRelationId;
			char *relationName = get_rel_name(relationId);
			Oid schemaOid = get_rel_namespace(relationId);
			char *schemaName = get_namespace_name(schemaOid);
			char *qualifiedTableName = quote_qualified_identifier(schemaName,
																  relationName);

			ereport(ERROR, (errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
							errmsg("the partition column of table %s cannot be NULL",
								   qualifiedTableName)));
		}

		/* find the partition column value */
		partitionColumnValue = columnValues[partitionColumnIndex];

		/* annoyingly this is evaluated twice, but at least we don't crash! */
		partitionColumnValue = CoerceColumnValue(partitionColumnValue, coercePath);
	}

	/*
	 * Find the shard interval and id for the partition column value for
	 * non-reference tables.
	 *
	 * For reference table, this function blindly returns the tables single
	 * shard.
	 */
	shardInterval = FindShardInterval(partitionColumnValue, copyDest->tableMetadata);
	if (shardInterval == NULL)
	{
		ereport(ERROR, (errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						errmsg("could not find shard for partition column "
							   "value")));
	}

	return shardInterval->shardId;
}