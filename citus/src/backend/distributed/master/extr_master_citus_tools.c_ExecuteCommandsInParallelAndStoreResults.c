#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  pgConn; } ;
struct TYPE_17__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  TYPE_2__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  CloseConnection (TYPE_2__*) ; 
 int FORCE_NEW_CONNECTION ; 
 int /*<<< orphan*/  FinishConnectionEstablishment (TYPE_2__*) ; 
 int GetConnectionStatusAndResult (TYPE_2__*,int*,TYPE_1__*) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 long RemoteTaskCheckInterval ; 
 int SendRemoteCommand (TYPE_2__*,char*) ; 
 TYPE_2__* StartNodeConnection (int,char*,int) ; 
 int /*<<< orphan*/  StoreErrorMessage (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,int) ; 
 TYPE_2__** palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_2__**) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 

__attribute__((used)) static void
ExecuteCommandsInParallelAndStoreResults(StringInfo *nodeNameArray, int *nodePortArray,
										 StringInfo *commandStringArray,
										 bool *statusArray, StringInfo *resultStringArray,
										 int commmandCount)
{
	int commandIndex = 0;
	MultiConnection **connectionArray =
		palloc0(commmandCount * sizeof(MultiConnection *));
	int finishedCount = 0;

	/* start connections asynchronously */
	for (commandIndex = 0; commandIndex < commmandCount; commandIndex++)
	{
		char *nodeName = nodeNameArray[commandIndex]->data;
		int nodePort = nodePortArray[commandIndex];
		int connectionFlags = FORCE_NEW_CONNECTION;
		connectionArray[commandIndex] =
			StartNodeConnection(connectionFlags, nodeName, nodePort);
	}

	/* establish connections */
	for (commandIndex = 0; commandIndex < commmandCount; commandIndex++)
	{
		MultiConnection *connection = connectionArray[commandIndex];
		StringInfo queryResultString = resultStringArray[commandIndex];
		char *nodeName = nodeNameArray[commandIndex]->data;
		int nodePort = nodePortArray[commandIndex];

		FinishConnectionEstablishment(connection);

		if (PQstatus(connection->pgConn) != CONNECTION_OK)
		{
			appendStringInfo(queryResultString, "failed to connect to %s:%d", nodeName,
							 (int) nodePort);
			statusArray[commandIndex] = false;
			connectionArray[commandIndex] = NULL;
			finishedCount++;
		}
		else
		{
			statusArray[commandIndex] = true;
		}
	}

	/* send queries at once */
	for (commandIndex = 0; commandIndex < commmandCount; commandIndex++)
	{
		int querySent = 0;
		MultiConnection *connection = connectionArray[commandIndex];
		char *queryString = commandStringArray[commandIndex]->data;
		StringInfo queryResultString = resultStringArray[commandIndex];

		/*
		 * If we don't have a connection, nothing to send, error string should already
		 * been filled.
		 */
		if (connection == NULL)
		{
			continue;
		}

		querySent = SendRemoteCommand(connection, queryString);
		if (querySent == 0)
		{
			StoreErrorMessage(connection, queryResultString);
			statusArray[commandIndex] = false;
			CloseConnection(connection);
			connectionArray[commandIndex] = NULL;
			finishedCount++;
		}
	}

	/* check for query results */
	while (finishedCount < commmandCount)
	{
		for (commandIndex = 0; commandIndex < commmandCount; commandIndex++)
		{
			MultiConnection *connection = connectionArray[commandIndex];
			StringInfo queryResultString = resultStringArray[commandIndex];
			bool success = false;
			bool queryFinished = false;

			if (connection == NULL)
			{
				continue;
			}

			queryFinished = GetConnectionStatusAndResult(connection, &success,
														 queryResultString);

			if (queryFinished)
			{
				finishedCount++;
				statusArray[commandIndex] = success;
				connectionArray[commandIndex] = NULL;
				CloseConnection(connection);
			}
		}

		CHECK_FOR_INTERRUPTS();

		if (finishedCount < commmandCount)
		{
			long sleepIntervalPerCycle = RemoteTaskCheckInterval * 1000L;
			pg_usleep(sleepIntervalPerCycle);
		}
	}

	pfree(connectionArray);
}