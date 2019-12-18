#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32 ;
struct TYPE_5__ {int /*<<< orphan*/  pgConn; } ;
typedef  scalar_t__ PostgresPollingStatusType ;
typedef  TYPE_1__ MultiConnection ;
typedef  int /*<<< orphan*/  ConnectStatus ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_BAD ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_BUSY ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_BUSY_READ ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_BUSY_WRITE ; 
 int /*<<< orphan*/  CLIENT_CONNECTION_READY ; 
 int /*<<< orphan*/  CLIENT_INVALID_CONNECT ; 
 TYPE_1__** ClientConnectionArray ; 
 int ClientConnectionReady (TYPE_1__*,scalar_t__) ; 
 scalar_t__* ClientPollingStatusArray ; 
 size_t INVALID_CONNECTION_ID ; 
 scalar_t__ PGRES_POLLING_FAILED ; 
 scalar_t__ PGRES_POLLING_OK ; 
 scalar_t__ PGRES_POLLING_READING ; 
 scalar_t__ PGRES_POLLING_WRITING ; 
 scalar_t__ PQconnectPoll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportConnectionError (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 

ConnectStatus
MultiClientConnectPoll(int32 connectionId)
{
	MultiConnection *connection = NULL;
	PostgresPollingStatusType pollingStatus = PGRES_POLLING_OK;
	ConnectStatus connectStatus = CLIENT_INVALID_CONNECT;

	Assert(connectionId != INVALID_CONNECTION_ID);
	connection = ClientConnectionArray[connectionId];
	Assert(connection != NULL);

	pollingStatus = ClientPollingStatusArray[connectionId];
	if (pollingStatus == PGRES_POLLING_OK)
	{
		connectStatus = CLIENT_CONNECTION_READY;
	}
	else if (pollingStatus == PGRES_POLLING_READING)
	{
		bool readReady = ClientConnectionReady(connection, PGRES_POLLING_READING);
		if (readReady)
		{
			ClientPollingStatusArray[connectionId] = PQconnectPoll(connection->pgConn);
			connectStatus = CLIENT_CONNECTION_BUSY;
		}
		else
		{
			connectStatus = CLIENT_CONNECTION_BUSY_READ;
		}
	}
	else if (pollingStatus == PGRES_POLLING_WRITING)
	{
		bool writeReady = ClientConnectionReady(connection, PGRES_POLLING_WRITING);
		if (writeReady)
		{
			ClientPollingStatusArray[connectionId] = PQconnectPoll(connection->pgConn);
			connectStatus = CLIENT_CONNECTION_BUSY;
		}
		else
		{
			connectStatus = CLIENT_CONNECTION_BUSY_WRITE;
		}
	}
	else if (pollingStatus == PGRES_POLLING_FAILED)
	{
		ReportConnectionError(connection, WARNING);

		connectStatus = CLIENT_CONNECTION_BAD;
	}

	return connectStatus;
}