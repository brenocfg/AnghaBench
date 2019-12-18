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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  WorkerNode ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/ * GetNodeTuple (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TupleToWorkerNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

WorkerNode *
FindWorkerNodeAnyCluster(const char *nodeName, int32 nodePort)
{
	WorkerNode *workerNode = NULL;

	Relation pgDistNode = heap_open(DistNodeRelationId(), AccessShareLock);
	TupleDesc tupleDescriptor = RelationGetDescr(pgDistNode);

	HeapTuple heapTuple = GetNodeTuple(nodeName, nodePort);
	if (heapTuple != NULL)
	{
		workerNode = TupleToWorkerNode(tupleDescriptor, heapTuple);
	}

	heap_close(pgDistNode, NoLock);
	return workerNode;
}