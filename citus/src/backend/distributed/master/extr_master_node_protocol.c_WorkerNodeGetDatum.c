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
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_3__ {scalar_t__ workerPort; int /*<<< orphan*/  workerName; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int CStringGetTextDatum (int /*<<< orphan*/ ) ; 
 int HeapTupleGetDatum (int /*<<< orphan*/ *) ; 
 int Int64GetDatum (int /*<<< orphan*/ ) ; 
 int WORKER_NODE_FIELDS ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static Datum
WorkerNodeGetDatum(WorkerNode *workerNode, TupleDesc tupleDescriptor)
{
	Datum values[WORKER_NODE_FIELDS];
	bool isNulls[WORKER_NODE_FIELDS];
	HeapTuple workerNodeTuple = NULL;
	Datum workerNodeDatum = 0;

	memset(values, 0, sizeof(values));
	memset(isNulls, false, sizeof(isNulls));

	values[0] = CStringGetTextDatum(workerNode->workerName);
	values[1] = Int64GetDatum((int64) workerNode->workerPort);

	workerNodeTuple = heap_form_tuple(tupleDescriptor, values, isNulls);
	workerNodeDatum = HeapTupleGetDatum(workerNodeTuple);

	return workerNodeDatum;
}