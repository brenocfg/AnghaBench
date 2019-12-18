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
struct TYPE_3__ {int /*<<< orphan*/ * initiatorProc; int /*<<< orphan*/  waitsFor; } ;
typedef  TYPE_1__ TransactionNode ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  DistributedTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  NIL ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static TransactionNode *
GetOrCreateTransactionNode(HTAB *adjacencyList, DistributedTransactionId *transactionId)
{
	TransactionNode *transactionNode = NULL;
	bool found = false;

	transactionNode = (TransactionNode *) hash_search(adjacencyList, transactionId,
													  HASH_ENTER, &found);
	if (!found)
	{
		transactionNode->waitsFor = NIL;
		transactionNode->initiatorProc = NULL;
	}

	return transactionNode;
}