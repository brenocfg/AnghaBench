#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_4__ {size_t edgeCount; TYPE_2__* edges; } ;
typedef  TYPE_1__ WaitGraph ;
struct TYPE_5__ {scalar_t__ waitingTransactionNum; scalar_t__ blockingTransactionNum; int /*<<< orphan*/  isBlockingXactWaiting; int /*<<< orphan*/  blockingTransactionStamp; int /*<<< orphan*/  blockingNodeId; int /*<<< orphan*/  blockingPid; int /*<<< orphan*/  waitingTransactionStamp; int /*<<< orphan*/  waitingNodeId; int /*<<< orphan*/  waitingPid; } ;
typedef  TYPE_2__ WaitEdge ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int Datum ;

/* Variables and functions */
 int BoolGetDatum (int /*<<< orphan*/ ) ; 
 int Int32GetDatum (int /*<<< orphan*/ ) ; 
 int Int64GetDatum (scalar_t__) ; 
 int /*<<< orphan*/ * SetupTuplestore (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tuplestore_donestoring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_putvalues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
ReturnWaitGraph(WaitGraph *waitGraph, FunctionCallInfo fcinfo)
{
	size_t curEdgeNum = 0;
	TupleDesc tupleDesc;
	Tuplestorestate *tupleStore = SetupTuplestore(fcinfo, &tupleDesc);

	/*
	 * Columns:
	 * 00: waiting_pid
	 * 01: waiting_node_id
	 * 02: waiting_transaction_num
	 * 03: waiting_transaction_stamp
	 * 04: blocking_pid
	 * 05: blocking__node_id
	 * 06: blocking_transaction_num
	 * 07: blocking_transaction_stamp
	 * 08: blocking_transaction_waiting
	 */
	for (curEdgeNum = 0; curEdgeNum < waitGraph->edgeCount; curEdgeNum++)
	{
		Datum values[9];
		bool nulls[9];
		WaitEdge *curEdge = &waitGraph->edges[curEdgeNum];

		memset(values, 0, sizeof(values));
		memset(nulls, 0, sizeof(nulls));

		values[0] = Int32GetDatum(curEdge->waitingPid);
		values[1] = Int32GetDatum(curEdge->waitingNodeId);
		if (curEdge->waitingTransactionNum != 0)
		{
			values[2] = Int64GetDatum(curEdge->waitingTransactionNum);
			values[3] = TimestampTzGetDatum(curEdge->waitingTransactionStamp);
		}
		else
		{
			nulls[2] = true;
			nulls[3] = true;
		}

		values[4] = Int32GetDatum(curEdge->blockingPid);
		values[5] = Int32GetDatum(curEdge->blockingNodeId);
		if (curEdge->blockingTransactionNum != 0)
		{
			values[6] = Int64GetDatum(curEdge->blockingTransactionNum);
			values[7] = TimestampTzGetDatum(curEdge->blockingTransactionStamp);
		}
		else
		{
			nulls[6] = true;
			nulls[7] = true;
		}
		values[8] = BoolGetDatum(curEdge->isBlockingXactWaiting);

		tuplestore_putvalues(tupleStore, tupleDesc, values, nulls);
	}

	/* clean up and return the tuplestore */
	tuplestore_donestoring(tupleStore);
}