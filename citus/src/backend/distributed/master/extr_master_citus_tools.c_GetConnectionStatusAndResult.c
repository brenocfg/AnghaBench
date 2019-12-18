#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pgConn; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ MultiConnection ;
typedef  scalar_t__ ConnStatusType ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 int EvaluateQueryResult (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQconsumeInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 scalar_t__ PQisBusy (int /*<<< orphan*/ ) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
GetConnectionStatusAndResult(MultiConnection *connection, bool *resultStatus,
							 StringInfo queryResultString)
{
	bool finished = true;
	ConnStatusType connectionStatus = PQstatus(connection->pgConn);
	int consumeInput = 0;
	PGresult *queryResult = NULL;
	bool success = false;

	*resultStatus = false;
	resetStringInfo(queryResultString);

	if (connectionStatus == CONNECTION_BAD)
	{
		appendStringInfo(queryResultString, "connection lost");
		return finished;
	}

	consumeInput = PQconsumeInput(connection->pgConn);
	if (consumeInput == 0)
	{
		appendStringInfo(queryResultString, "query result unavailable");
		return finished;
	}

	/* check later if busy */
	if (PQisBusy(connection->pgConn) != 0)
	{
		finished = false;
		return finished;
	}

	/* query result is available at this point */
	queryResult = PQgetResult(connection->pgConn);
	success = EvaluateQueryResult(connection, queryResult, queryResultString);
	PQclear(queryResult);

	*resultStatus = success;
	finished = true;
	return true;
}