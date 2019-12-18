#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {scalar_t__ shardState; } ;
typedef  TYPE_1__ ShardPlacement ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FILE_FINALIZED ; 
 scalar_t__ FILE_INACTIVE ; 
 TYPE_1__* SearchShardPlacementInList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ShardPlacementList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
EnsureShardCanBeRepaired(int64 shardId, char *sourceNodeName, int32 sourceNodePort,
						 char *targetNodeName, int32 targetNodePort)
{
	List *shardPlacementList = ShardPlacementList(shardId);
	ShardPlacement *sourcePlacement = NULL;
	ShardPlacement *targetPlacement = NULL;
	bool missingSourceOk = false;
	bool missingTargetOk = false;

	sourcePlacement = SearchShardPlacementInList(shardPlacementList, sourceNodeName,
												 sourceNodePort, missingSourceOk);
	if (sourcePlacement->shardState != FILE_FINALIZED)
	{
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("source placement must be in finalized state")));
	}

	targetPlacement = SearchShardPlacementInList(shardPlacementList, targetNodeName,
												 targetNodePort, missingTargetOk);
	if (targetPlacement->shardState != FILE_INACTIVE)
	{
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("target placement must be in inactive state")));
	}
}