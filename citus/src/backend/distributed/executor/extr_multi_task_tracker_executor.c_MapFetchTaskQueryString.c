#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_7__ {int /*<<< orphan*/  currentNodeIndex; } ;
typedef  TYPE_1__ TaskExecution ;
struct TYPE_8__ {scalar_t__ taskType; int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; TYPE_1__* taskExecution; int /*<<< orphan*/ * taskPlacementList; int /*<<< orphan*/  upstreamTaskId; int /*<<< orphan*/  partitionId; } ;
typedef  TYPE_2__ Task ;
struct TYPE_9__ {char* nodeName; int /*<<< orphan*/  nodePort; } ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  TYPE_3__ ShardPlacement ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MAP_OUTPUT_FETCH_COMMAND ; 
 scalar_t__ MAP_OUTPUT_FETCH_TASK ; 
 scalar_t__ MAP_TASK ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* list_nth (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeStringInfo () ; 

__attribute__((used)) static StringInfo
MapFetchTaskQueryString(Task *mapFetchTask, Task *mapTask)
{
	StringInfo mapFetchQueryString = NULL;
	uint32 partitionFileId = mapFetchTask->partitionId;
	uint32 mergeTaskId = mapFetchTask->upstreamTaskId;

	/* find the node name/port for map task's execution */
	List *mapTaskPlacementList = mapTask->taskPlacementList;
	TaskExecution *mapTaskExecution = mapTask->taskExecution;
	uint32 currentIndex = mapTaskExecution->currentNodeIndex;

	ShardPlacement *mapTaskPlacement = list_nth(mapTaskPlacementList, currentIndex);
	char *mapTaskNodeName = mapTaskPlacement->nodeName;
	uint32 mapTaskNodePort = mapTaskPlacement->nodePort;

	Assert(mapFetchTask->taskType == MAP_OUTPUT_FETCH_TASK);
	Assert(mapTask->taskType == MAP_TASK);

	mapFetchQueryString = makeStringInfo();
	appendStringInfo(mapFetchQueryString, MAP_OUTPUT_FETCH_COMMAND,
					 mapTask->jobId, mapTask->taskId, partitionFileId,
					 mergeTaskId, /* fetch results to merge task */
					 mapTaskNodeName, mapTaskNodePort);

	return mapFetchQueryString;
}