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
struct TYPE_4__ {int /*<<< orphan*/ * pgConn; } ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  LogRemoteCommand (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  PQisnonblocking (int /*<<< orphan*/ *) ; 
 int PQsendQueryParams (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/  const*,char const* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 

int
SendRemoteCommandParams(MultiConnection *connection, const char *command,
						int parameterCount, const Oid *parameterTypes,
						const char *const *parameterValues)
{
	PGconn *pgConn = connection->pgConn;
	int rc = 0;

	LogRemoteCommand(connection, command);

	/*
	 * Don't try to send command if connection is entirely gone
	 * (PQisnonblocking() would crash).
	 */
	if (!pgConn || PQstatus(pgConn) != CONNECTION_OK)
	{
		return 0;
	}

	Assert(PQisnonblocking(pgConn));

	rc = PQsendQueryParams(pgConn, command, parameterCount, parameterTypes,
						   parameterValues, NULL, NULL, 0);

	return rc;
}