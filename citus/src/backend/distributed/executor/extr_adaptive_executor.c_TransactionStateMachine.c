#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_3__* currentTask; TYPE_6__* connection; TYPE_2__* workerPool; } ;
typedef  TYPE_1__ WorkerSession ;
struct TYPE_22__ {int /*<<< orphan*/  idleConnectionCount; TYPE_7__* distributedExecution; } ;
typedef  TYPE_2__ WorkerPool ;
struct TYPE_23__ {TYPE_4__* shardCommandExecution; } ;
typedef  TYPE_3__ TaskPlacementExecution ;
struct TYPE_27__ {int /*<<< orphan*/  isTransaction; } ;
struct TYPE_25__ {int transactionState; } ;
struct TYPE_26__ {int /*<<< orphan*/  connectionState; int /*<<< orphan*/  pgConn; TYPE_5__ remoteTransaction; } ;
struct TYPE_24__ {int expectResults; int gotResults; } ;
typedef  TYPE_4__ ShardCommandExecution ;
typedef  int RemoteTransactionState ;
typedef  TYPE_5__ RemoteTransaction ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_6__ MultiConnection ;
typedef  TYPE_7__ DistributedExecution ;

/* Variables and functions */
 int /*<<< orphan*/  Activate2PCIfModifyingTransactionExpandsToNewNode (TYPE_1__*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CheckConnectionReady (TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MULTI_CONNECTION_LOST ; 
 int /*<<< orphan*/  MarkRemoteTransactionCritical (TYPE_6__*) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlacementExecutionDone (TYPE_3__*,int) ; 
 TYPE_3__* PopPlacementExecution (TYPE_1__*) ; 
#define  REMOTE_TRANS_CLEARING_RESULTS 132 
#define  REMOTE_TRANS_INVALID 131 
#define  REMOTE_TRANS_SENT_BEGIN 130 
#define  REMOTE_TRANS_SENT_COMMAND 129 
#define  REMOTE_TRANS_STARTED 128 
 int ReceiveResults (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ReportResultError (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int StartPlacementExecutionOnSession (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  StartRemoteTransactionBegin (TYPE_6__*) ; 
 int /*<<< orphan*/  UpdateConnectionWaitFlags (TYPE_1__*,int) ; 
 int WL_SOCKET_READABLE ; 
 int WL_SOCKET_WRITEABLE ; 

__attribute__((used)) static void
TransactionStateMachine(WorkerSession *session)
{
	WorkerPool *workerPool = session->workerPool;
	DistributedExecution *execution = workerPool->distributedExecution;

	MultiConnection *connection = session->connection;
	RemoteTransaction *transaction = &(connection->remoteTransaction);
	RemoteTransactionState currentState;

	do {
		currentState = transaction->transactionState;

		if (!CheckConnectionReady(session))
		{
			/* connection is busy, no state transitions to make */
			break;
		}

		switch (currentState)
		{
			case REMOTE_TRANS_INVALID:
			{
				if (execution->isTransaction)
				{
					/* if we're expanding the nodes in a transaction, use 2PC */
					Activate2PCIfModifyingTransactionExpandsToNewNode(session);

					/* need to open a transaction block first */
					StartRemoteTransactionBegin(connection);

					transaction->transactionState = REMOTE_TRANS_CLEARING_RESULTS;
				}
				else
				{
					TaskPlacementExecution *placementExecution = NULL;
					bool placementExecutionStarted = false;

					placementExecution = PopPlacementExecution(session);
					if (placementExecution == NULL)
					{
						/*
						 * No tasks are ready to be executed at the moment. But we
						 * still mark the socket readable to get any notices if exists.
						 */
						UpdateConnectionWaitFlags(session, WL_SOCKET_READABLE);

						break;
					}

					placementExecutionStarted =
						StartPlacementExecutionOnSession(placementExecution, session);
					if (!placementExecutionStarted)
					{
						/* no need to continue, connection is lost */
						Assert(session->connection->connectionState ==
							   MULTI_CONNECTION_LOST);

						return;
					}

					transaction->transactionState = REMOTE_TRANS_SENT_COMMAND;
				}

				UpdateConnectionWaitFlags(session,
										  WL_SOCKET_READABLE | WL_SOCKET_WRITEABLE);
				break;
			}

			case REMOTE_TRANS_SENT_BEGIN:
			case REMOTE_TRANS_CLEARING_RESULTS:
			{
				PGresult *result = NULL;

				result = PQgetResult(connection->pgConn);
				if (result != NULL)
				{
					if (!IsResponseOK(result))
					{
						/* query failures are always hard errors */
						ReportResultError(connection, result, ERROR);
					}

					PQclear(result);

					/* wake up WaitEventSetWait */
					UpdateConnectionWaitFlags(session,
											  WL_SOCKET_READABLE | WL_SOCKET_WRITEABLE);

					break;
				}

				if (session->currentTask != NULL)
				{
					TaskPlacementExecution *placementExecution = session->currentTask;
					bool succeeded = true;

					/*
					 * Once we finished a task on a connection, we no longer
					 * allow that connection to fail.
					 */
					MarkRemoteTransactionCritical(connection);

					session->currentTask = NULL;

					PlacementExecutionDone(placementExecution, succeeded);

					/* connection is ready to use for executing commands */
					workerPool->idleConnectionCount++;
				}

				/* connection needs to be writeable to send next command */
				UpdateConnectionWaitFlags(session,
										  WL_SOCKET_READABLE | WL_SOCKET_WRITEABLE);

				if (execution->isTransaction)
				{
					transaction->transactionState = REMOTE_TRANS_STARTED;
				}
				else
				{
					transaction->transactionState = REMOTE_TRANS_INVALID;
				}
				break;
			}

			case REMOTE_TRANS_STARTED:
			{
				TaskPlacementExecution *placementExecution = NULL;
				bool placementExecutionStarted = false;

				placementExecution = PopPlacementExecution(session);
				if (placementExecution == NULL)
				{
					/* no tasks are ready to be executed at the moment */
					UpdateConnectionWaitFlags(session, WL_SOCKET_READABLE);
					break;
				}

				placementExecutionStarted =
					StartPlacementExecutionOnSession(placementExecution, session);
				if (!placementExecutionStarted)
				{
					/* no need to continue, connection is lost */
					Assert(session->connection->connectionState == MULTI_CONNECTION_LOST);

					return;
				}

				transaction->transactionState = REMOTE_TRANS_SENT_COMMAND;
				break;
			}

			case REMOTE_TRANS_SENT_COMMAND:
			{
				bool fetchDone = false;
				TaskPlacementExecution *placementExecution = session->currentTask;
				ShardCommandExecution *shardCommandExecution =
					placementExecution->shardCommandExecution;
				bool storeRows = shardCommandExecution->expectResults;

				if (shardCommandExecution->gotResults)
				{
					/* already received results from another replica */
					storeRows = false;
				}

				fetchDone = ReceiveResults(session, storeRows);
				if (!fetchDone)
				{
					break;
				}

				shardCommandExecution->gotResults = true;
				transaction->transactionState = REMOTE_TRANS_CLEARING_RESULTS;
				break;
			}

			default:
			{
				break;
			}
		}
	}
	/* iterate in case we can perform multiple transitions at once */
	while (transaction->transactionState != currentState);
}