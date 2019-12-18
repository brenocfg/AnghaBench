#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_8__ {int /*<<< orphan*/  relationId; int /*<<< orphan*/  shardId; } ;
struct TYPE_7__ {char* nodeName; scalar_t__ shardState; int /*<<< orphan*/  placementId; int /*<<< orphan*/  groupId; int /*<<< orphan*/  nodePort; } ;
typedef  TYPE_1__ ShardPlacement ;
typedef  TYPE_2__ ShardInterval ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyShardCommandList (TYPE_2__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EnsureNoModificationsHaveBeenDone () ; 
 scalar_t__ FILE_FINALIZED ; 
 TYPE_1__* FinalizedShardPlacement (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetNextPlacementId () ; 
 int /*<<< orphan*/  GroupForNode (char*,int) ; 
 int /*<<< orphan*/  InsertShardPlacementRow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 char* PlacementUpsertCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SearchShardPlacementInList (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  SendCommandListToWorkerInSingleTransaction (char*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendCommandToWorkers (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ShardPlacementList (int /*<<< orphan*/ ) ; 
 scalar_t__ ShouldSyncTableMetadata (int /*<<< orphan*/ ) ; 
 char* TableOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateShardPlacementState (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WORKERS_WITH_METADATA ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ReplicateShardToNode(ShardInterval *shardInterval, char *nodeName, int nodePort)
{
	uint64 shardId = shardInterval->shardId;

	bool missingOk = false;
	ShardPlacement *sourceShardPlacement = FinalizedShardPlacement(shardId, missingOk);
	char *srcNodeName = sourceShardPlacement->nodeName;
	uint32 srcNodePort = sourceShardPlacement->nodePort;
	bool includeData = true;
	List *ddlCommandList =
		CopyShardCommandList(shardInterval, srcNodeName, srcNodePort, includeData);

	List *shardPlacementList = ShardPlacementList(shardId);
	bool missingWorkerOk = true;
	ShardPlacement *targetPlacement = SearchShardPlacementInList(shardPlacementList,
																 nodeName, nodePort,
																 missingWorkerOk);
	char *tableOwner = TableOwner(shardInterval->relationId);

	/*
	 * Although this function is used for reference tables and reference table shard
	 * placements always have shardState = FILE_FINALIZED, in case of an upgrade of
	 * a non-reference table to reference table, unhealty placements may exist. In
	 * this case, we repair the shard placement and update its state in
	 * pg_dist_placement table.
	 */
	if (targetPlacement == NULL || targetPlacement->shardState != FILE_FINALIZED)
	{
		uint64 placementId = 0;
		int32 groupId = 0;

		ereport(NOTICE, (errmsg("Replicating reference table \"%s\" to the node %s:%d",
								get_rel_name(shardInterval->relationId), nodeName,
								nodePort)));

		EnsureNoModificationsHaveBeenDone();
		SendCommandListToWorkerInSingleTransaction(nodeName, nodePort, tableOwner,
												   ddlCommandList);
		if (targetPlacement == NULL)
		{
			groupId = GroupForNode(nodeName, nodePort);

			placementId = GetNextPlacementId();
			InsertShardPlacementRow(shardId, placementId, FILE_FINALIZED, 0, groupId);
		}
		else
		{
			groupId = targetPlacement->groupId;
			placementId = targetPlacement->placementId;
			UpdateShardPlacementState(placementId, FILE_FINALIZED);
		}

		/*
		 * Although ReplicateShardToAllNodes is used only for reference tables,
		 * during the upgrade phase, the placements are created before the table is
		 * marked as a reference table. All metadata (including the placement
		 * metadata) will be copied to workers after all reference table changed
		 * are finished.
		 */
		if (ShouldSyncTableMetadata(shardInterval->relationId))
		{
			char *placementCommand = PlacementUpsertCommand(shardId, placementId,
															FILE_FINALIZED, 0,
															groupId);

			SendCommandToWorkers(WORKERS_WITH_METADATA, placementCommand);
		}
	}
}