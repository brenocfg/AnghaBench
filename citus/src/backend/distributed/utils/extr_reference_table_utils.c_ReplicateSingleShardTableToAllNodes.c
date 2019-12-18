#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_4__ {int /*<<< orphan*/  shardId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertToReferenceTableMetadata (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CopyShardForeignConstraintCommandList (TYPE_1__*) ; 
 int /*<<< orphan*/  CreateTableMetadataOnWorkers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * LoadShardIntervalList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ReplicateShardToAllNodes (TYPE_1__*) ; 
 scalar_t__ TableReferenced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ReplicateSingleShardTableToAllNodes(Oid relationId)
{
	List *shardIntervalList = LoadShardIntervalList(relationId);
	ShardInterval *shardInterval = (ShardInterval *) linitial(shardIntervalList);
	uint64 shardId = shardInterval->shardId;

	List *foreignConstraintCommandList = CopyShardForeignConstraintCommandList(
		shardInterval);

	if (foreignConstraintCommandList != NIL || TableReferenced(relationId))
	{
		char *relationName = get_rel_name(relationId);
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot upgrade to reference table"),
						errdetail("Relation \"%s\" is part of a foreign constraint. "
								  "Foreign key constraints are not allowed "
								  "from or to reference tables.", relationName)));
	}

	/*
	 * ReplicateShardToAllNodes function opens separate transactions (i.e., not part
	 * of any coordinated transactions) to each worker and replicates given shard to all
	 * workers. If a worker already has a healthy replica of given shard, it skips that
	 * worker to prevent copying unnecessary data.
	 */
	ReplicateShardToAllNodes(shardInterval);

	/*
	 * We need to update metadata tables to mark this table as reference table. We modify
	 * pg_dist_partition, pg_dist_colocation and pg_dist_shard tables in
	 * ConvertToReferenceTableMetadata function.
	 */
	ConvertToReferenceTableMetadata(relationId, shardId);

	/*
	 * After the table has been officially marked as a reference table, we need to create
	 * the reference table itself and insert its pg_dist_partition, pg_dist_shard and
	 * existing pg_dist_placement rows.
	 */
	CreateTableMetadataOnWorkers(relationId);
}