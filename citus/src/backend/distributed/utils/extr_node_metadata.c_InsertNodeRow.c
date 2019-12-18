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
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  isNulls ;
typedef  int int32 ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_3__ {char* nodeRack; int /*<<< orphan*/  shouldHaveShards; int /*<<< orphan*/  nodeRole; int /*<<< orphan*/  isActive; int /*<<< orphan*/  metadataSynced; int /*<<< orphan*/  hasMetadata; int /*<<< orphan*/  groupId; int /*<<< orphan*/  nodeCluster; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_1__ NodeMetadata ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int Datum ;

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
 int BoolGetDatum (int /*<<< orphan*/ ) ; 
 int CStringGetDatum (int /*<<< orphan*/ ) ; 
 int CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CitusInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int DirectFunctionCall1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int Int32GetDatum (int /*<<< orphan*/ ) ; 
 int Natts_pg_dist_node ; 
 int /*<<< orphan*/  NoLock ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int UInt32GetDatum (int) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namein ; 

__attribute__((used)) static void
InsertNodeRow(int nodeid, char *nodeName, int32 nodePort, NodeMetadata *nodeMetadata)
{
	Relation pgDistNode = NULL;
	TupleDesc tupleDescriptor = NULL;
	HeapTuple heapTuple = NULL;
	Datum values[Natts_pg_dist_node];
	bool isNulls[Natts_pg_dist_node];

	Datum nodeClusterStringDatum = CStringGetDatum(nodeMetadata->nodeCluster);
	Datum nodeClusterNameDatum = DirectFunctionCall1(namein, nodeClusterStringDatum);

	/* form new shard tuple */
	memset(values, 0, sizeof(values));
	memset(isNulls, false, sizeof(isNulls));

	values[Anum_pg_dist_node_nodeid - 1] = UInt32GetDatum(nodeid);
	values[Anum_pg_dist_node_groupid - 1] = Int32GetDatum(nodeMetadata->groupId);
	values[Anum_pg_dist_node_nodename - 1] = CStringGetTextDatum(nodeName);
	values[Anum_pg_dist_node_nodeport - 1] = UInt32GetDatum(nodePort);
	values[Anum_pg_dist_node_noderack - 1] = CStringGetTextDatum(nodeMetadata->nodeRack);
	values[Anum_pg_dist_node_hasmetadata - 1] = BoolGetDatum(nodeMetadata->hasMetadata);
	values[Anum_pg_dist_node_metadatasynced - 1] = BoolGetDatum(
		nodeMetadata->metadataSynced);
	values[Anum_pg_dist_node_isactive - 1] = BoolGetDatum(nodeMetadata->isActive);
	values[Anum_pg_dist_node_noderole - 1] = ObjectIdGetDatum(nodeMetadata->nodeRole);
	values[Anum_pg_dist_node_nodecluster - 1] = nodeClusterNameDatum;
	values[Anum_pg_dist_node_shouldhaveshards - 1] = BoolGetDatum(
		nodeMetadata->shouldHaveShards);

	pgDistNode = heap_open(DistNodeRelationId(), RowExclusiveLock);

	tupleDescriptor = RelationGetDescr(pgDistNode);
	heapTuple = heap_form_tuple(tupleDescriptor, values, isNulls);

	CatalogTupleInsert(pgDistNode, heapTuple);

	CitusInvalidateRelcacheByRelid(DistNodeRelationId());

	/* increment the counter so that next command can see the row */
	CommandCounterIncrement();

	/* close relation */
	heap_close(pgDistNode, NoLock);
}