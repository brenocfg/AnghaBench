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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CreateReferenceTableColocationId () ; 
 int /*<<< orphan*/  DISTRIBUTE_BY_NONE ; 
 int /*<<< orphan*/  DeleteColocationGroupIfNoTablesBelong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeletePartitionRow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteShardRow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertIntoPgDistPartition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertShardRow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REPLICATION_MODEL_2PC ; 
 char ShardStorageType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TableColocationId (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ConvertToReferenceTableMetadata(Oid relationId, uint64 shardId)
{
	uint32 currentColocationId = TableColocationId(relationId);
	uint32 newColocationId = CreateReferenceTableColocationId();
	Var *distributionColumn = NULL;
	char shardStorageType = ShardStorageType(relationId);
	text *shardMinValue = NULL;
	text *shardMaxValue = NULL;

	/* delete old metadata rows */
	DeletePartitionRow(relationId);
	DeleteColocationGroupIfNoTablesBelong(currentColocationId);
	DeleteShardRow(shardId);

	/* insert new metadata rows */
	InsertIntoPgDistPartition(relationId, DISTRIBUTE_BY_NONE, distributionColumn,
							  newColocationId, REPLICATION_MODEL_2PC);
	InsertShardRow(relationId, shardId, shardStorageType, shardMinValue, shardMaxValue);
}