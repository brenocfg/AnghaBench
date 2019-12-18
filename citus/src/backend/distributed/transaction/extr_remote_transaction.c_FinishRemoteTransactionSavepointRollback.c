#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int transactionRecovering; int transactionFailed; int /*<<< orphan*/  transactionState; } ;
struct TYPE_8__ {TYPE_1__ remoteTransaction; } ;
typedef  int /*<<< orphan*/  SubTransactionId ;
typedef  TYPE_1__ RemoteTransaction ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_2__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ForgetResults (TYPE_2__*) ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  HandleRemoteTransactionResultError (TYPE_2__*,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REMOTE_TRANS_STARTED ; 

__attribute__((used)) static void
FinishRemoteTransactionSavepointRollback(MultiConnection *connection, SubTransactionId
										 subId)
{
	const bool raiseErrors = false;
	RemoteTransaction *transaction = &connection->remoteTransaction;

	PGresult *result = GetRemoteCommandResult(connection, raiseErrors);
	if (!IsResponseOK(result))
	{
		HandleRemoteTransactionResultError(connection, result, raiseErrors);
	}

	/* ROLLBACK TO SAVEPOINT succeeded, check if it recovers the transaction */
	else if (transaction->transactionRecovering)
	{
		transaction->transactionFailed = false;
		transaction->transactionRecovering = false;
	}

	PQclear(result);
	ForgetResults(connection);

	/* reset transaction state so the executor can accept next commands in transaction */
	transaction->transactionState = REMOTE_TRANS_STARTED;
}