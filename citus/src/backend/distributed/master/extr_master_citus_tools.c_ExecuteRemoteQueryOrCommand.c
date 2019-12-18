#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {int /*<<< orphan*/  pgConn; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  CloseConnection (TYPE_1__*) ; 
 int EvaluateQueryResult (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int FORCE_NEW_CONNECTION ; 
 TYPE_1__* GetNodeConnection (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (TYPE_1__*,int) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendRemoteCommand (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static bool
ExecuteRemoteQueryOrCommand(char *nodeName, uint32 nodePort, char *queryString,
							StringInfo queryResultString)
{
	int connectionFlags = FORCE_NEW_CONNECTION;
	MultiConnection *connection =
		GetNodeConnection(connectionFlags, nodeName, nodePort);
	bool success = false;
	PGresult *queryResult = NULL;
	bool raiseInterrupts = true;

	if (PQstatus(connection->pgConn) != CONNECTION_OK)
	{
		appendStringInfo(queryResultString, "failed to connect to %s:%d", nodeName,
						 (int) nodePort);
		return false;
	}

	SendRemoteCommand(connection, queryString);
	queryResult = GetRemoteCommandResult(connection, raiseInterrupts);
	success = EvaluateQueryResult(connection, queryResult, queryResultString);

	PQclear(queryResult);

	/* close the connection */
	CloseConnection(connection);

	return success;
}