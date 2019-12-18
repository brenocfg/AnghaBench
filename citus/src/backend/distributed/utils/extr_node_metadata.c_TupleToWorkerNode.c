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
typedef  int /*<<< orphan*/  isNullArray ;
struct TYPE_3__ {int /*<<< orphan*/  nodeCluster; void* shouldHaveShards; int /*<<< orphan*/  nodeRole; void* isActive; void* metadataSynced; void* hasMetadata; int /*<<< orphan*/  workerRack; int /*<<< orphan*/  workerName; int /*<<< orphan*/  groupId; void* workerPort; void* nodeId; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/ * Name ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_dist_node_groupid ; 
 int Anum_pg_dist_node_hasmetadata ; 
 int Anum_pg_dist_node_isactive ; 
 int Anum_pg_dist_node_metadatasynced ; 
 int Anum_pg_dist_node_nodecluster ; 
 int Anum_pg_dist_node_nodeid ; 
 int Anum_pg_dist_node_nodename ; 
 int Anum_pg_dist_node_nodeport ; 
 int Anum_pg_dist_node_noderack ; 
 int Anum_pg_dist_node_noderole ; 
 int Anum_pg_dist_node_shouldhaveshards ; 
 int /*<<< orphan*/  Assert (int) ; 
 void* DatumGetBool (int /*<<< orphan*/ ) ; 
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 void* DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHasNulls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int Natts_pg_dist_node ; 
 char* TextDatumGetCString (char*) ; 
 int /*<<< orphan*/  WORKER_LENGTH ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WorkerNode *
TupleToWorkerNode(TupleDesc tupleDescriptor, HeapTuple heapTuple)
{
	WorkerNode *workerNode = NULL;
	Datum datumArray[Natts_pg_dist_node];
	bool isNullArray[Natts_pg_dist_node];
	char *nodeName = NULL;
	char *nodeRack = NULL;

	Assert(!HeapTupleHasNulls(heapTuple));

	/*
	 * This function can be called before "ALTER TABLE ... ADD COLUMN nodecluster ...",
	 * therefore heap_deform_tuple() won't set the isNullArray for this column. We
	 * initialize it true to be safe in that case.
	 */
	memset(isNullArray, true, sizeof(isNullArray));

	/*
	 * We use heap_deform_tuple() instead of heap_getattr() to expand tuple
	 * to contain missing values when ALTER TABLE ADD COLUMN happens.
	 */
	heap_deform_tuple(heapTuple, tupleDescriptor, datumArray, isNullArray);

	nodeName = DatumGetCString(datumArray[Anum_pg_dist_node_nodename - 1]);
	nodeRack = DatumGetCString(datumArray[Anum_pg_dist_node_noderack - 1]);

	workerNode = (WorkerNode *) palloc0(sizeof(WorkerNode));
	workerNode->nodeId = DatumGetUInt32(datumArray[Anum_pg_dist_node_nodeid - 1]);
	workerNode->workerPort = DatumGetUInt32(datumArray[Anum_pg_dist_node_nodeport - 1]);
	workerNode->groupId = DatumGetInt32(datumArray[Anum_pg_dist_node_groupid - 1]);
	strlcpy(workerNode->workerName, TextDatumGetCString(nodeName), WORKER_LENGTH);
	strlcpy(workerNode->workerRack, TextDatumGetCString(nodeRack), WORKER_LENGTH);
	workerNode->hasMetadata = DatumGetBool(datumArray[Anum_pg_dist_node_hasmetadata - 1]);
	workerNode->metadataSynced =
		DatumGetBool(datumArray[Anum_pg_dist_node_metadatasynced - 1]);
	workerNode->isActive = DatumGetBool(datumArray[Anum_pg_dist_node_isactive - 1]);
	workerNode->nodeRole = DatumGetObjectId(datumArray[Anum_pg_dist_node_noderole - 1]);
	workerNode->shouldHaveShards = DatumGetBool(
		datumArray[Anum_pg_dist_node_shouldhaveshards -
				   1]);

	/*
	 * nodecluster column can be missing. In the case of extension creation/upgrade,
	 * master_initialize_node_metadata function is called before the nodecluster
	 * column is added to pg_dist_node table.
	 */
	if (!isNullArray[Anum_pg_dist_node_nodecluster - 1])
	{
		Name nodeClusterName =
			DatumGetName(datumArray[Anum_pg_dist_node_nodecluster - 1]);
		char *nodeClusterString = NameStr(*nodeClusterName);
		strlcpy(workerNode->nodeCluster, nodeClusterString, NAMEDATALEN);
	}

	return workerNode;
}