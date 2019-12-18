#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  replace ;
struct TYPE_11__ {int /*<<< orphan*/  workerPort; int /*<<< orphan*/  workerName; int /*<<< orphan*/  nodeId; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_12__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__* HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
#define  Anum_pg_dist_node_isactive 129 
#define  Anum_pg_dist_node_shouldhaveshards 128 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CitusInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* GetNodeTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Natts_pg_dist_node ; 
 int /*<<< orphan*/  NoLock ; 
 char* NodeStateUpdateCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SendCommandToWorkers (int /*<<< orphan*/ ,char*) ; 
 char* ShouldHaveShardsUpdateCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* TupleToWorkerNode (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  WORKERS_WITH_METADATA ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static WorkerNode *
SetWorkerColumn(WorkerNode *workerNode, int columnIndex, Datum value)
{
	Relation pgDistNode = heap_open(DistNodeRelationId(), RowExclusiveLock);
	TupleDesc tupleDescriptor = RelationGetDescr(pgDistNode);
	HeapTuple heapTuple = GetNodeTuple(workerNode->workerName, workerNode->workerPort);
	WorkerNode *newWorkerNode = NULL;

	Datum values[Natts_pg_dist_node];
	bool isnull[Natts_pg_dist_node];
	bool replace[Natts_pg_dist_node];
	char *metadataSyncCommand = NULL;


	switch (columnIndex)
	{
		case Anum_pg_dist_node_isactive:
		{
			metadataSyncCommand = NodeStateUpdateCommand(workerNode->nodeId,
														 DatumGetBool(value));
			break;
		}

		case Anum_pg_dist_node_shouldhaveshards:
		{
			metadataSyncCommand = ShouldHaveShardsUpdateCommand(workerNode->nodeId,
																DatumGetBool(value));
			break;
		}

		default:
		{
			ereport(ERROR, (errmsg("could not find valid entry for node \"%s:%d\"",
								   workerNode->workerName, workerNode->workerPort)));
		}
	}

	if (heapTuple == NULL)
	{
		ereport(ERROR, (errmsg("could not find valid entry for node \"%s:%d\"",
							   workerNode->workerName, workerNode->workerPort)));
	}

	memset(replace, 0, sizeof(replace));
	values[columnIndex - 1] = value;
	isnull[columnIndex - 1] = false;
	replace[columnIndex - 1] = true;

	heapTuple = heap_modify_tuple(heapTuple, tupleDescriptor, values, isnull, replace);

	CatalogTupleUpdate(pgDistNode, &heapTuple->t_self, heapTuple);

	CitusInvalidateRelcacheByRelid(DistNodeRelationId());
	CommandCounterIncrement();

	newWorkerNode = TupleToWorkerNode(tupleDescriptor, heapTuple);

	heap_close(pgDistNode, NoLock);

	/* we also update the column at worker nodes */
	SendCommandToWorkers(WORKERS_WITH_METADATA, metadataSyncCommand);
	return newWorkerNode;
}