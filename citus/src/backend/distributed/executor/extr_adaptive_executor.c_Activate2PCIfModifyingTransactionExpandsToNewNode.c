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
struct TYPE_5__ {int /*<<< orphan*/  connection; TYPE_1__* workerPool; } ;
typedef  TYPE_2__ WorkerSession ;
struct TYPE_4__ {int /*<<< orphan*/ * distributedExecution; } ;
typedef  int /*<<< orphan*/  DistributedExecution ;

/* Variables and functions */
 scalar_t__ COMMIT_PROTOCOL_2PC ; 
 int /*<<< orphan*/  ConnectionModifiedPlacement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoordinatedTransactionUse2PC () ; 
 scalar_t__ DistributedExecutionModifiesDatabase (int /*<<< orphan*/ *) ; 
 scalar_t__ MultiShardCommitProtocol ; 
 scalar_t__ TransactionModifiedDistributedTable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Activate2PCIfModifyingTransactionExpandsToNewNode(WorkerSession *session)
{
	DistributedExecution *execution = NULL;

	if (MultiShardCommitProtocol != COMMIT_PROTOCOL_2PC)
	{
		/* we don't need 2PC, so no need to continue */
		return;
	}

	execution = session->workerPool->distributedExecution;
	if (TransactionModifiedDistributedTable(execution) &&
		DistributedExecutionModifiesDatabase(execution) &&
		!ConnectionModifiedPlacement(session->connection))
	{
		/*
		 * We already did a modification, but not on the connection that we
		 * just opened, which means we're now going to make modifications
		 * over multiple connections. Activate 2PC!
		 */
		CoordinatedTransactionUse2PC();
	}
}