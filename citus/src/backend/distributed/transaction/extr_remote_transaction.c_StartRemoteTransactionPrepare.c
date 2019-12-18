#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ transactionState; int /*<<< orphan*/  preparedName; int /*<<< orphan*/  transactionFailed; } ;
struct MultiConnection {int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; TYPE_3__ remoteTransaction; } ;
struct TYPE_7__ {int /*<<< orphan*/  groupId; } ;
typedef  TYPE_1__ WorkerNode ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  TYPE_3__ RemoteTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  Assign2PCIdentifier (struct MultiConnection*) ; 
 TYPE_1__* FindWorkerNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HandleRemoteTransactionConnectionError (struct MultiConnection*,int const) ; 
 int /*<<< orphan*/  LogTransactionRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REMOTE_TRANS_INVALID ; 
 scalar_t__ REMOTE_TRANS_PREPARING ; 
 int /*<<< orphan*/  SendRemoteCommand (struct MultiConnection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  quote_literal_cstr (int /*<<< orphan*/ ) ; 

void
StartRemoteTransactionPrepare(struct MultiConnection *connection)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;
	StringInfoData command;
	const bool raiseErrors = true;
	WorkerNode *workerNode = NULL;

	/* can't prepare a nonexistant transaction */
	Assert(transaction->transactionState != REMOTE_TRANS_INVALID);

	/* can't prepare in a failed transaction */
	Assert(!transaction->transactionFailed);

	/* can't prepare if already started to prepare/abort/commit */
	Assert(transaction->transactionState < REMOTE_TRANS_PREPARING);

	Assign2PCIdentifier(connection);

	/* log transactions to workers in pg_dist_transaction */
	workerNode = FindWorkerNode(connection->hostname, connection->port);
	if (workerNode != NULL)
	{
		LogTransactionRecord(workerNode->groupId, transaction->preparedName);
	}

	initStringInfo(&command);
	appendStringInfo(&command, "PREPARE TRANSACTION %s",
					 quote_literal_cstr(transaction->preparedName));

	if (!SendRemoteCommand(connection, command.data))
	{
		HandleRemoteTransactionConnectionError(connection, raiseErrors);
	}
	else
	{
		transaction->transactionState = REMOTE_TRANS_PREPARING;
	}
}