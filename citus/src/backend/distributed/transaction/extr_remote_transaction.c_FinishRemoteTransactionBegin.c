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
struct TYPE_2__ {scalar_t__ transactionState; int /*<<< orphan*/  transactionFailed; int /*<<< orphan*/  lastQueuedSubXact; int /*<<< orphan*/  lastSuccessfulSubXact; } ;
struct MultiConnection {int /*<<< orphan*/  pgConn; TYPE_1__ remoteTransaction; } ;
typedef  TYPE_1__ RemoteTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int ClearResults (struct MultiConnection*,int) ; 
 scalar_t__ PQTRANS_INTRANS ; 
 scalar_t__ PQtransactionStatus (int /*<<< orphan*/ ) ; 
 scalar_t__ REMOTE_TRANS_STARTED ; 
 scalar_t__ REMOTE_TRANS_STARTING ; 

void
FinishRemoteTransactionBegin(struct MultiConnection *connection)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;
	bool clearSuccessful = true;
	bool raiseErrors = true;

	Assert(transaction->transactionState == REMOTE_TRANS_STARTING);

	clearSuccessful = ClearResults(connection, raiseErrors);
	if (clearSuccessful)
	{
		transaction->transactionState = REMOTE_TRANS_STARTED;
		transaction->lastSuccessfulSubXact = transaction->lastQueuedSubXact;
	}

	if (!transaction->transactionFailed)
	{
		Assert(PQtransactionStatus(connection->pgConn) == PQTRANS_INTRANS);
	}
}