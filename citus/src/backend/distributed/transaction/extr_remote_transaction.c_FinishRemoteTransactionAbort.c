#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ transactionState; } ;
struct TYPE_10__ {TYPE_1__ remoteTransaction; } ;
typedef  TYPE_1__ RemoteTransaction ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_2__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ClearResults (TYPE_2__*,int const) ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  HandleRemoteTransactionResultError (TYPE_2__*,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ REMOTE_TRANS_2PC_ABORTING ; 
 scalar_t__ REMOTE_TRANS_ABORTED ; 
 int /*<<< orphan*/  ShutdownConnection (TYPE_2__*) ; 
 int /*<<< orphan*/  WarnAboutLeakedPreparedTransaction (TYPE_2__*,int const) ; 

void
FinishRemoteTransactionAbort(MultiConnection *connection)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;
	const bool raiseErrors = false;

	if (transaction->transactionState == REMOTE_TRANS_2PC_ABORTING)
	{
		PGresult *result = GetRemoteCommandResult(connection, raiseErrors);
		if (!IsResponseOK(result))
		{
			const bool isCommit = false;

			HandleRemoteTransactionResultError(connection, result, raiseErrors);

			WarnAboutLeakedPreparedTransaction(connection, isCommit);
		}

		PQclear(result);
	}

	/*
	 * Try to consume results of any in-progress commands. In the 1PC case
	 * this is also where we consume the result of the ROLLBACK.
	 *
	 * If we don't succeed the connection will be in a bad state, so we close it.
	 */
	if (!ClearResults(connection, raiseErrors))
	{
		ShutdownConnection(connection);
	}

	transaction->transactionState = REMOTE_TRANS_ABORTED;
}