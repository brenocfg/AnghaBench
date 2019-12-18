#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  size_t int32 ;
struct TYPE_6__ {int /*<<< orphan*/  pgConn; } ;
typedef  TYPE_1__ MultiConnection ;
typedef  scalar_t__ ConnStatusType ;

/* Variables and functions */
 size_t AllocateConnectionId () ; 
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ CONNECTION_OK ; 
 TYPE_1__** ClientConnectionArray ; 
 int /*<<< orphan*/ * ClientPollingStatusArray ; 
 int /*<<< orphan*/  CloseConnection (TYPE_1__*) ; 
 int /*<<< orphan*/  ERRCODE_ACTIVE_SQL_TRANSACTION ; 
 int /*<<< orphan*/  ERROR ; 
 int FORCE_NEW_CONNECTION ; 
 size_t INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  PGRES_POLLING_WRITING ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportConnectionError (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* StartNodeUserDatabaseConnection (int,char const*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ XACT_MODIFICATION_NONE ; 
 scalar_t__ XactModificationLevel ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

int32
MultiClientConnectStart(const char *nodeName, uint32 nodePort, const char *nodeDatabase,
						const char *userName)
{
	MultiConnection *connection = NULL;
	ConnStatusType connStatusType = CONNECTION_OK;
	int32 connectionId = AllocateConnectionId();
	int connectionFlags = FORCE_NEW_CONNECTION; /* no cached connections for now */

	if (connectionId == INVALID_CONNECTION_ID)
	{
		ereport(WARNING, (errmsg("could not allocate connection in connection pool")));
		return connectionId;
	}

	if (XactModificationLevel > XACT_MODIFICATION_NONE)
	{
		ereport(ERROR, (errcode(ERRCODE_ACTIVE_SQL_TRANSACTION),
						errmsg("cannot open new connections after the first modification "
							   "command within a transaction")));
	}

	/* prepare asynchronous request for worker node connection */
	connection = StartNodeUserDatabaseConnection(connectionFlags, nodeName, nodePort,
												 userName, nodeDatabase);
	connStatusType = PQstatus(connection->pgConn);

	/*
	 * If prepared, we save the connection, and set its initial polling status
	 * to PGRES_POLLING_WRITING as specified in "Database Connection Control
	 * Functions" section of the PostgreSQL documentation.
	 */
	if (connStatusType != CONNECTION_BAD)
	{
		ClientConnectionArray[connectionId] = connection;
		ClientPollingStatusArray[connectionId] = PGRES_POLLING_WRITING;
	}
	else
	{
		ReportConnectionError(connection, WARNING);
		CloseConnection(connection);

		connectionId = INVALID_CONNECTION_ID;
	}

	return connectionId;
}