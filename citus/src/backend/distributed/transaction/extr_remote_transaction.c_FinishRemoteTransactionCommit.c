#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ transactionState; } ;
struct TYPE_9__ {int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; TYPE_1__ remoteTransaction; } ;
typedef  TYPE_1__ RemoteTransaction ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_2__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ForgetResults (TYPE_2__*) ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  HandleRemoteTransactionResultError (TYPE_2__*,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ REMOTE_TRANS_1PC_ABORTING ; 
 scalar_t__ REMOTE_TRANS_1PC_COMMITTING ; 
 scalar_t__ REMOTE_TRANS_2PC_ABORTING ; 
 scalar_t__ REMOTE_TRANS_2PC_COMMITTING ; 
 scalar_t__ REMOTE_TRANS_ABORTED ; 
 scalar_t__ REMOTE_TRANS_COMMITTED ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  WarnAboutLeakedPreparedTransaction (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
FinishRemoteTransactionCommit(MultiConnection *connection)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;
	PGresult *result = NULL;
	const bool raiseErrors = false;
	const bool isCommit = true;

	Assert(transaction->transactionState == REMOTE_TRANS_1PC_ABORTING ||
		   transaction->transactionState == REMOTE_TRANS_1PC_COMMITTING ||
		   transaction->transactionState == REMOTE_TRANS_2PC_COMMITTING);

	result = GetRemoteCommandResult(connection, raiseErrors);

	if (!IsResponseOK(result))
	{
		HandleRemoteTransactionResultError(connection, result, raiseErrors);

		/*
		 * Failing in this state means that we will often not know whether
		 * the the commit has succeeded (particularly in case of network
		 * troubles).
		 *
		 * XXX: It might be worthwhile to discern cases where we got a
		 * proper error back from postgres (i.e. COMMIT was received but
		 * produced an error) from cases where the connection failed
		 * before getting a reply.
		 */

		if (transaction->transactionState == REMOTE_TRANS_1PC_COMMITTING)
		{
			ereport(WARNING, (errmsg("failed to commit transaction on %s:%d",
									 connection->hostname, connection->port)));
		}
		else if (transaction->transactionState == REMOTE_TRANS_2PC_COMMITTING)
		{
			ereport(WARNING, (errmsg("failed to commit transaction on %s:%d",
									 connection->hostname, connection->port)));
			WarnAboutLeakedPreparedTransaction(connection, isCommit);
		}
	}
	else if (transaction->transactionState == REMOTE_TRANS_1PC_ABORTING ||
			 transaction->transactionState == REMOTE_TRANS_2PC_ABORTING)
	{
		transaction->transactionState = REMOTE_TRANS_ABORTED;
	}
	else
	{
		transaction->transactionState = REMOTE_TRANS_COMMITTED;
	}

	PQclear(result);

	ForgetResults(connection);
}