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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * FinalizedShardPlacementList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * RemoteFinalizedShardPlacementList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * masterConnection ; 

__attribute__((used)) static List *
MasterShardPlacementList(uint64 shardId)
{
	List *finalizedPlacementList = NIL;
	if (masterConnection == NULL)
	{
		finalizedPlacementList = FinalizedShardPlacementList(shardId);
	}
	else
	{
		finalizedPlacementList = RemoteFinalizedShardPlacementList(shardId);
	}

	return finalizedPlacementList;
}