#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  queryString; int /*<<< orphan*/ * taskPlacementList; } ;
typedef  TYPE_1__ Task ;
struct TYPE_16__ {int /*<<< orphan*/  pgConn; } ;
struct TYPE_15__ {int placementIndex; int /*<<< orphan*/  explainOutputList; } ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  int /*<<< orphan*/  ShardPlacement ;
typedef  TYPE_3__ RemoteExplainPlan ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ MultiConnection ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ExplainState ;

/* Variables and functions */
 int /*<<< orphan*/  BeginOrContinueCoordinatedTransaction () ; 
 TYPE_2__* BuildRemoteExplainQuery (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  ExecuteCriticalRemoteCommand (TYPE_4__*,char*) ; 
 int ExecuteOptionalRemoteCommand (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ForgetResults (TYPE_4__*) ; 
 TYPE_4__* GetPlacementConnection (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadFirstColumnAsText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoteTransactionBeginIfNecessary (TYPE_4__*) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_nth (int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static RemoteExplainPlan *
RemoteExplain(Task *task, ExplainState *es)
{
	StringInfo explainQuery = NULL;
	List *taskPlacementList = task->taskPlacementList;
	int placementCount = list_length(taskPlacementList);
	int placementIndex = 0;
	RemoteExplainPlan *remotePlan = NULL;

	remotePlan = (RemoteExplainPlan *) palloc0(sizeof(RemoteExplainPlan));
	explainQuery = BuildRemoteExplainQuery(task->queryString, es);

	/*
	 * Use a coordinated transaction to ensure that we open a transaction block
	 * such that we can set a savepoint.
	 */
	BeginOrContinueCoordinatedTransaction();

	for (placementIndex = 0; placementIndex < placementCount; placementIndex++)
	{
		ShardPlacement *taskPlacement = list_nth(taskPlacementList, placementIndex);
		MultiConnection *connection = NULL;
		PGresult *queryResult = NULL;
		int connectionFlags = 0;
		int executeResult = 0;

		remotePlan->placementIndex = placementIndex;

		connection = GetPlacementConnection(connectionFlags, taskPlacement, NULL);

		/* try other placements if we fail to connect this one */
		if (PQstatus(connection->pgConn) != CONNECTION_OK)
		{
			continue;
		}

		RemoteTransactionBeginIfNecessary(connection);

		/*
		 * Start a savepoint for the explain query. After running the explain
		 * query, we will rollback to this savepoint. This saves us from side
		 * effects of EXPLAIN ANALYZE on DML queries.
		 */
		ExecuteCriticalRemoteCommand(connection, "SAVEPOINT citus_explain_savepoint");

		/* run explain query */
		executeResult = ExecuteOptionalRemoteCommand(connection, explainQuery->data,
													 &queryResult);
		if (executeResult != 0)
		{
			PQclear(queryResult);
			ForgetResults(connection);

			continue;
		}

		/* read explain query results */
		remotePlan->explainOutputList = ReadFirstColumnAsText(queryResult);

		PQclear(queryResult);
		ForgetResults(connection);

		/* rollback to the savepoint */
		ExecuteCriticalRemoteCommand(connection,
									 "ROLLBACK TO SAVEPOINT citus_explain_savepoint");

		if (remotePlan->explainOutputList != NIL)
		{
			break;
		}
	}

	return remotePlan;
}