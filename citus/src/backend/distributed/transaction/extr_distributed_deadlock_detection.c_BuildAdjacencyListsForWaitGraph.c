#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_12__ {int edgeCount; TYPE_2__* edges; } ;
typedef  TYPE_1__ WaitGraph ;
struct TYPE_13__ {int /*<<< orphan*/  blockingTransactionStamp; int /*<<< orphan*/  blockingTransactionNum; int /*<<< orphan*/  blockingNodeId; int /*<<< orphan*/  waitingTransactionStamp; int /*<<< orphan*/  waitingTransactionNum; int /*<<< orphan*/  waitingNodeId; } ;
typedef  TYPE_2__ WaitEdge ;
struct TYPE_14__ {int /*<<< orphan*/  waitsFor; } ;
typedef  TYPE_3__ TransactionNode ;
struct TYPE_16__ {int member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; int /*<<< orphan*/  match; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_4__ HASHCTL ;
typedef  TYPE_5__ DistributedTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DistributedTransactionIdCompare ; 
 int /*<<< orphan*/  DistributedTransactionIdHash ; 
 TYPE_3__* GetOrCreateTransactionNode (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int HASH_COMPARE ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int HASH_FUNCTION ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

extern HTAB *
BuildAdjacencyListsForWaitGraph(WaitGraph *waitGraph)
{
	HASHCTL info;
	uint32 hashFlags = 0;
	HTAB *adjacencyList = NULL;
	int edgeIndex = 0;
	int edgeCount = waitGraph->edgeCount;

	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(DistributedTransactionId);
	info.entrysize = sizeof(TransactionNode);
	info.hash = DistributedTransactionIdHash;
	info.match = DistributedTransactionIdCompare;
	info.hcxt = CurrentMemoryContext;
	hashFlags = (HASH_ELEM | HASH_FUNCTION | HASH_CONTEXT | HASH_COMPARE);

	adjacencyList = hash_create("distributed deadlock detection", 64, &info, hashFlags);

	for (edgeIndex = 0; edgeIndex < edgeCount; edgeIndex++)
	{
		WaitEdge *edge = &waitGraph->edges[edgeIndex];
		TransactionNode *waitingTransaction = NULL;
		TransactionNode *blockingTransaction = NULL;
		bool transactionOriginator = false;

		DistributedTransactionId waitingId = {
			edge->waitingNodeId,
			transactionOriginator,
			edge->waitingTransactionNum,
			edge->waitingTransactionStamp
		};

		DistributedTransactionId blockingId = {
			edge->blockingNodeId,
			transactionOriginator,
			edge->blockingTransactionNum,
			edge->blockingTransactionStamp
		};

		waitingTransaction =
			GetOrCreateTransactionNode(adjacencyList, &waitingId);
		blockingTransaction =
			GetOrCreateTransactionNode(adjacencyList, &blockingId);

		waitingTransaction->waitsFor = lappend(waitingTransaction->waitsFor,
											   blockingTransaction);
	}

	return adjacencyList;
}