#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ transactionState; int /*<<< orphan*/  preparedName; } ;
struct MultiConnection {int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; TYPE_1__ remoteTransaction; } ;
typedef  TYPE_1__ RemoteTransaction ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ClearResults (struct MultiConnection*,int const) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (struct MultiConnection*,int const) ; 
 int /*<<< orphan*/  HandleRemoteTransactionResultError (struct MultiConnection*,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ REMOTE_TRANS_ABORTED ; 
 scalar_t__ REMOTE_TRANS_PREPARED ; 
 scalar_t__ REMOTE_TRANS_PREPARING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
FinishRemoteTransactionPrepare(struct MultiConnection *connection)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;
	PGresult *result = NULL;
	const bool raiseErrors = true;

	Assert(transaction->transactionState == REMOTE_TRANS_PREPARING);

	result = GetRemoteCommandResult(connection, raiseErrors);

	if (!IsResponseOK(result))
	{
		transaction->transactionState = REMOTE_TRANS_ABORTED;
		HandleRemoteTransactionResultError(connection, result, raiseErrors);
	}
	else
	{
		transaction->transactionState = REMOTE_TRANS_PREPARED;
	}

	PQclear(result);

	/*
	 * Try to consume results of PREPARE TRANSACTION command. If we don't
	 * succeed, rollback the transaction. Note that we've not committed on
	 * any node yet, and we're not sure about the state of the worker node.
	 * So rollbacking seems to be the safest action if the worker is
	 * in a state where it can actually rollback.
	 */
	if (!ClearResults(connection, raiseErrors))
	{
		ereport(ERROR, (errmsg("failed to prepare transaction '%s' on host %s:%d",
							   transaction->preparedName, connection->hostname,
							   connection->port),
						errhint("Try re-running the command.")));
	}
}