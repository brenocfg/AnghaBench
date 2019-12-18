#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int commandsSent; TYPE_3__* currentTask; TYPE_7__* connection; TYPE_2__* workerPool; } ;
typedef  TYPE_1__ WorkerSession ;
struct TYPE_19__ {int /*<<< orphan*/  idleConnectionCount; int /*<<< orphan*/  unusedConnectionCount; TYPE_8__* distributedExecution; } ;
typedef  TYPE_2__ WorkerPool ;
struct TYPE_20__ {int /*<<< orphan*/  executionState; int /*<<< orphan*/ * shardPlacement; TYPE_5__* shardCommandExecution; } ;
typedef  TYPE_3__ TaskPlacementExecution ;
struct TYPE_21__ {char* queryString; } ;
typedef  TYPE_4__ Task ;
struct TYPE_25__ {TYPE_6__* paramListInfo; } ;
struct TYPE_24__ {void* connectionState; int /*<<< orphan*/  pgConn; } ;
struct TYPE_23__ {int numParams; } ;
struct TYPE_22__ {TYPE_4__* task; } ;
typedef  int /*<<< orphan*/  ShardPlacement ;
typedef  TYPE_5__ ShardCommandExecution ;
typedef  TYPE_6__* ParamListInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_7__ MultiConnection ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_8__ DistributedExecution ;

/* Variables and functions */
 int /*<<< orphan*/  AssignPlacementListToConnection (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  ExtractParametersForRemoteExecution (TYPE_6__*,int /*<<< orphan*/ **,char const***) ; 
 void* MULTI_CONNECTION_LOST ; 
 int /*<<< orphan*/  PLACEMENT_EXECUTION_RUNNING ; 
 int PQsetSingleRowMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PlacementAccessListForTask (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int SendRemoteCommand (TYPE_7__*,char*) ; 
 int SendRemoteCommandParams (TYPE_7__*,char*,int,int /*<<< orphan*/ *,char const**) ; 
 TYPE_6__* copyParamList (TYPE_6__*) ; 

__attribute__((used)) static bool
StartPlacementExecutionOnSession(TaskPlacementExecution *placementExecution,
								 WorkerSession *session)
{
	WorkerPool *workerPool = session->workerPool;
	DistributedExecution *execution = workerPool->distributedExecution;
	ParamListInfo paramListInfo = execution->paramListInfo;
	MultiConnection *connection = session->connection;
	ShardCommandExecution *shardCommandExecution =
		placementExecution->shardCommandExecution;
	Task *task = shardCommandExecution->task;
	ShardPlacement *taskPlacement = placementExecution->shardPlacement;
	List *placementAccessList = PlacementAccessListForTask(task, taskPlacement);
	char *queryString = task->queryString;
	int querySent = 0;
	int singleRowMode = 0;

	/*
	 * Make sure that subsequent commands on the same placement
	 * use the same connection.
	 */
	AssignPlacementListToConnection(placementAccessList, connection);

	/* one more command is sent over the session */
	session->commandsSent++;

	if (session->commandsSent == 1)
	{
		/* first time we send a command, consider the connection used (not unused) */
		workerPool->unusedConnectionCount--;
	}

	/* connection is going to be in use */
	workerPool->idleConnectionCount--;
	session->currentTask = placementExecution;
	placementExecution->executionState = PLACEMENT_EXECUTION_RUNNING;

	if (paramListInfo != NULL)
	{
		int parameterCount = paramListInfo->numParams;
		Oid *parameterTypes = NULL;
		const char **parameterValues = NULL;

		/* force evaluation of bound params */
		paramListInfo = copyParamList(paramListInfo);

		ExtractParametersForRemoteExecution(paramListInfo, &parameterTypes,
											&parameterValues);
		querySent = SendRemoteCommandParams(connection, queryString, parameterCount,
											parameterTypes, parameterValues);
	}
	else
	{
		querySent = SendRemoteCommand(connection, queryString);
	}

	if (querySent == 0)
	{
		connection->connectionState = MULTI_CONNECTION_LOST;
		return false;
	}

	singleRowMode = PQsetSingleRowMode(connection->pgConn);
	if (singleRowMode == 0)
	{
		connection->connectionState = MULTI_CONNECTION_LOST;
		return false;
	}

	return true;
}