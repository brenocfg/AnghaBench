#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ taskType; int /*<<< orphan*/ * relationShardList; } ;
typedef  TYPE_1__ Task ;
struct TYPE_7__ {int /*<<< orphan*/  groupId; } ;
typedef  scalar_t__ ShardPlacementAccessType ;
typedef  int /*<<< orphan*/  ShardPlacementAccess ;
typedef  TYPE_2__ ShardPlacement ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * BuildPlacementDDLList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BuildPlacementSelectList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreatePlacementAccess (TYPE_2__*,scalar_t__) ; 
 scalar_t__ DDL_TASK ; 
 scalar_t__ MODIFY_TASK ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ PLACEMENT_ACCESS_DDL ; 
 scalar_t__ PLACEMENT_ACCESS_DML ; 
 scalar_t__ PLACEMENT_ACCESS_SELECT ; 
 scalar_t__ VACUUM_ANALYZE_TASK ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
PlacementAccessListForTask(Task *task, ShardPlacement *taskPlacement)
{
	List *placementAccessList = NIL;
	List *relationShardList = task->relationShardList;
	bool addAnchorAccess = false;
	ShardPlacementAccessType accessType = PLACEMENT_ACCESS_SELECT;

	if (task->taskType == MODIFY_TASK)
	{
		/* DML command */
		addAnchorAccess = true;
		accessType = PLACEMENT_ACCESS_DML;
	}
	else if (task->taskType == DDL_TASK || task->taskType == VACUUM_ANALYZE_TASK)
	{
		/* DDL command */
		addAnchorAccess = true;
		accessType = PLACEMENT_ACCESS_DDL;
	}
	else if (relationShardList == NIL)
	{
		/* SELECT query that does not touch any shard placements */
		addAnchorAccess = true;
		accessType = PLACEMENT_ACCESS_SELECT;
	}

	if (addAnchorAccess)
	{
		ShardPlacementAccess *placementAccess =
			CreatePlacementAccess(taskPlacement, accessType);

		placementAccessList = lappend(placementAccessList, placementAccess);
	}

	/*
	 * We've already added anchor shardId's placement access to the list. Now,
	 * add the other placements in the relationShardList.
	 */
	if (accessType == PLACEMENT_ACCESS_DDL)
	{
		/*
		 * All relations appearing inter-shard DDL commands should be marked
		 * with DDL access.
		 */
		List *relationShardAccessList =
			BuildPlacementDDLList(taskPlacement->groupId, relationShardList);

		placementAccessList = list_concat(placementAccessList, relationShardAccessList);
	}
	else
	{
		/*
		 * In case of SELECTs or DML's, we add SELECT placement accesses to the
		 * elements in relationShardList. For SELECT queries, it is trivial, since
		 * the query is literally accesses the relationShardList in the same query.
		 *
		 * For DMLs, create placement accesses for placements that appear in a
		 * subselect.
		 */
		List *relationShardAccessList =
			BuildPlacementSelectList(taskPlacement->groupId, relationShardList);

		placementAccessList = list_concat(placementAccessList, relationShardAccessList);
	}

	return placementAccessList;
}