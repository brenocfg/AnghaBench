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
typedef  size_t int32 ;
struct TYPE_4__ {int /*<<< orphan*/  pgConn; } ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyLogRedaction (char const*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__** ClientConnectionArray ; 
 size_t INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int SendRemoteCommand (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 char* pchomp (int /*<<< orphan*/ ) ; 

bool
MultiClientSendQuery(int32 connectionId, const char *query)
{
	MultiConnection *connection = NULL;
	bool success = true;
	int querySent = 0;

	Assert(connectionId != INVALID_CONNECTION_ID);
	connection = ClientConnectionArray[connectionId];
	Assert(connection != NULL);

	querySent = SendRemoteCommand(connection, query);
	if (querySent == 0)
	{
		char *errorMessage = pchomp(PQerrorMessage(connection->pgConn));

		/*
		 * query might include the user query coming from the taskTracker
		 * code path, that's why we hash it, too. Otherwise, this code
		 * path is generally exercised for the kind of errors that
		 * we cannot send the queries that Citus itself produced.
		 */
		ereport(WARNING, (errmsg("could not send remote query \"%s\"",
								 ApplyLogRedaction(query)),
						  errdetail("Client error: %s",
									ApplyLogRedaction(errorMessage))));

		success = false;
	}

	return success;
}