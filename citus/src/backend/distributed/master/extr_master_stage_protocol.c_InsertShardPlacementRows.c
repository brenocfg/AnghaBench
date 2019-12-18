#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_2__ {int /*<<< orphan*/  groupId; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  ShardPlacement ;
typedef  int /*<<< orphan*/  RelayFileState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_FINALIZED ; 
 int /*<<< orphan*/  INVALID_PLACEMENT_ID ; 
 int /*<<< orphan*/  InsertShardPlacementRow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LoadShardPlacement (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ *,int) ; 

List *
InsertShardPlacementRows(Oid relationId, int64 shardId, List *workerNodeList,
						 int workerStartIndex, int replicationFactor)
{
	int workerNodeCount = list_length(workerNodeList);
	int attemptNumber = 0;
	int placementsInserted = 0;
	List *insertedShardPlacements = NIL;

	for (attemptNumber = 0; attemptNumber < replicationFactor; attemptNumber++)
	{
		int workerNodeIndex = (workerStartIndex + attemptNumber) % workerNodeCount;
		WorkerNode *workerNode = (WorkerNode *) list_nth(workerNodeList, workerNodeIndex);
		uint32 nodeGroupId = workerNode->groupId;
		const RelayFileState shardState = FILE_FINALIZED;
		const uint64 shardSize = 0;
		uint64 shardPlacementId = 0;
		ShardPlacement *shardPlacement = NULL;

		shardPlacementId = InsertShardPlacementRow(shardId, INVALID_PLACEMENT_ID,
												   shardState, shardSize, nodeGroupId);
		shardPlacement = LoadShardPlacement(shardId, shardPlacementId);
		insertedShardPlacements = lappend(insertedShardPlacements, shardPlacement);

		placementsInserted++;
		if (placementsInserted >= replicationFactor)
		{
			break;
		}
	}

	return insertedShardPlacements;
}