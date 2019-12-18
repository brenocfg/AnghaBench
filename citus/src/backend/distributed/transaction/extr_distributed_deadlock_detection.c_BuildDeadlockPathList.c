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
typedef  int /*<<< orphan*/  TransactionNode ;
struct TYPE_3__ {int currentStackDepth; } ;
typedef  TYPE_1__ QueuedTransactionNode ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
BuildDeadlockPathList(QueuedTransactionNode *cycledTransactionNode,
					  TransactionNode **transactionNodeStack,
					  List **deadlockPath)
{
	int deadlockStackDepth = cycledTransactionNode->currentStackDepth;
	int stackIndex = 0;

	*deadlockPath = NIL;

	for (stackIndex = 0; stackIndex < deadlockStackDepth; stackIndex++)
	{
		*deadlockPath = lappend(*deadlockPath, transactionNodeStack[stackIndex]);
	}
}