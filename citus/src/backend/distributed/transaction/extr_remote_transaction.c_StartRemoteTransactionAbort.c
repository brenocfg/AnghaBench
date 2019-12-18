#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ transactionState; int /*<<< orphan*/  preparedName; } ;
struct TYPE_16__ {TYPE_2__ remoteTransaction; } ;
struct TYPE_14__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ RemoteTransaction ;
typedef  TYPE_3__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ClearResultsIfReady (TYPE_3__*) ; 
 int /*<<< orphan*/  ForgetResults (TYPE_3__*) ; 
 int /*<<< orphan*/  HandleRemoteTransactionConnectionError (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  MarkRemoteTransactionFailed (TYPE_3__*,int const) ; 
 scalar_t__ REMOTE_TRANS_1PC_ABORTING ; 
 scalar_t__ REMOTE_TRANS_2PC_ABORTING ; 
 scalar_t__ REMOTE_TRANS_INVALID ; 
 scalar_t__ REMOTE_TRANS_PREPARED ; 
 scalar_t__ REMOTE_TRANS_PREPARING ; 
 int /*<<< orphan*/  SendRemoteCommand (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  ShutdownConnection (TYPE_3__*) ; 
 int /*<<< orphan*/  WarnAboutLeakedPreparedTransaction (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  quote_literal_cstr (int /*<<< orphan*/ ) ; 

void
StartRemoteTransactionAbort(MultiConnection *connection)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;
	const bool raiseErrors = false;
	const bool isNotCommit = false;

	Assert(transaction->transactionState != REMOTE_TRANS_INVALID);

	/*
	 * Clear previous results, so we have a better chance to send ROLLBACK
	 * [PREPARED]. If we've previously sent a PREPARE TRANSACTION, we always
	 * want to wait for that result, as that shouldn't take long and will
	 * reserve resources.  But if there's another query running, we don't want
	 * to wait, because a long running statement may be running, so force it to
	 * be killed in that case.
	 */
	if (transaction->transactionState == REMOTE_TRANS_PREPARING ||
		transaction->transactionState == REMOTE_TRANS_PREPARED)
	{
		StringInfoData command;

		/* await PREPARE TRANSACTION results, closing the connection would leave it dangling */
		ForgetResults(connection);

		initStringInfo(&command);
		appendStringInfo(&command, "ROLLBACK PREPARED %s",
						 quote_literal_cstr(transaction->preparedName));

		if (!SendRemoteCommand(connection, command.data))
		{
			HandleRemoteTransactionConnectionError(connection, raiseErrors);

			WarnAboutLeakedPreparedTransaction(connection, isNotCommit);
		}
		else
		{
			transaction->transactionState = REMOTE_TRANS_2PC_ABORTING;
		}
	}
	else
	{
		/*
		 * In case of a cancellation, the connection might still be working
		 * on some commands. Try to consume the results such that the
		 * connection can be reused, but do not want to wait for commands
		 * to finish. Instead we just close the connection if the command
		 * is still busy.
		 */
		if (!ClearResultsIfReady(connection))
		{
			ShutdownConnection(connection);

			/* FinishRemoteTransactionAbort will emit warning */
			return;
		}

		if (!SendRemoteCommand(connection, "ROLLBACK"))
		{
			/* no point in reporting a likely redundant message */
			MarkRemoteTransactionFailed(connection, raiseErrors);
		}
		else
		{
			transaction->transactionState = REMOTE_TRANS_1PC_ABORTING;
		}
	}
}