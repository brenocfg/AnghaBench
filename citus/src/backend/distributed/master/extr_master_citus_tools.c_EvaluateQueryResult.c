#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  MultiConnection ;
typedef  scalar_t__ ExecStatusType ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 char* PQcmdStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StoreErrorMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool
EvaluateQueryResult(MultiConnection *connection, PGresult *queryResult,
					StringInfo queryResultString)
{
	bool success = false;

	ExecStatusType resultStatus = PQresultStatus(queryResult);
	if (resultStatus == PGRES_COMMAND_OK)
	{
		char *commandStatus = PQcmdStatus(queryResult);
		appendStringInfo(queryResultString, "%s", commandStatus);
		success = true;
	}
	else if (resultStatus == PGRES_TUPLES_OK)
	{
		int ntuples = PQntuples(queryResult);
		int nfields = PQnfields(queryResult);

		/* error if query returns more than 1 rows, or more than 1 fields */
		if (nfields != 1)
		{
			appendStringInfo(queryResultString,
							 "expected a single column in query target");
		}
		else if (ntuples > 1)
		{
			appendStringInfo(queryResultString,
							 "expected a single row in query result");
		}
		else
		{
			int row = 0;
			int column = 0;
			if (!PQgetisnull(queryResult, row, column))
			{
				char *queryResultValue = PQgetvalue(queryResult, row, column);
				appendStringInfo(queryResultString, "%s", queryResultValue);
			}
			success = true;
		}
	}
	else
	{
		StoreErrorMessage(connection, queryResultString);
	}

	return success;
}