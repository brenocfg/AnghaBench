#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ transactionState; int /*<<< orphan*/  preparedName; scalar_t__ transactionFailed; } ;
struct TYPE_13__ {TYPE_2__ remoteTransaction; } ;
struct TYPE_11__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ RemoteTransaction ;
typedef  TYPE_3__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ForgetResults (TYPE_3__*) ; 
 int /*<<< orphan*/  HandleRemoteTransactionConnectionError (TYPE_3__*,int const) ; 
 scalar_t__ REMOTE_TRANS_1PC_ABORTING ; 
 scalar_t__ REMOTE_TRANS_1PC_COMMITTING ; 
 scalar_t__ REMOTE_TRANS_2PC_COMMITTING ; 
 scalar_t__ REMOTE_TRANS_INVALID ; 
 scalar_t__ REMOTE_TRANS_PREPARED ; 
 int /*<<< orphan*/  SendRemoteCommand (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  WarnAboutLeakedPreparedTransaction (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  quote_literal_cstr (int /*<<< orphan*/ ) ; 

void
StartRemoteTransactionCommit(MultiConnection *connection)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;
	const bool raiseErrors = false;
	const bool isCommit = true;

	/* can only commit if transaction is in progress */
	Assert(transaction->transactionState != REMOTE_TRANS_INVALID);

	/* can't commit if we already started to commit or abort */
	Assert(transaction->transactionState < REMOTE_TRANS_1PC_ABORTING);

	if (transaction->transactionFailed)
	{
		/* abort the transaction if it failed */
		transaction->transactionState = REMOTE_TRANS_1PC_ABORTING;

		/*
		 * Try sending an ROLLBACK; Depending on the state that won't
		 * succeed, but let's try.  Have to clear previous results
		 * first.
		 */
		ForgetResults(connection); /* try to clear pending stuff */
		if (!SendRemoteCommand(connection, "ROLLBACK"))
		{
			/* no point in reporting a likely redundant message */
		}
	}
	else if (transaction->transactionState == REMOTE_TRANS_PREPARED)
	{
		/* commit the prepared transaction */
		StringInfoData command;

		initStringInfo(&command);
		appendStringInfo(&command, "COMMIT PREPARED %s",
						 quote_literal_cstr(transaction->preparedName));

		transaction->transactionState = REMOTE_TRANS_2PC_COMMITTING;

		if (!SendRemoteCommand(connection, command.data))
		{
			HandleRemoteTransactionConnectionError(connection, raiseErrors);

			WarnAboutLeakedPreparedTransaction(connection, isCommit);
		}
	}
	else
	{
		/* initiate remote transaction commit */
		transaction->transactionState = REMOTE_TRANS_1PC_COMMITTING;

		if (!SendRemoteCommand(connection, "COMMIT"))
		{
			/*
			 * For a moment there I thought we were in trouble.
			 *
			 * Failing in this state means that we don't know whether the the
			 * commit has succeeded.
			 */
			HandleRemoteTransactionConnectionError(connection, raiseErrors);
		}
	}
}