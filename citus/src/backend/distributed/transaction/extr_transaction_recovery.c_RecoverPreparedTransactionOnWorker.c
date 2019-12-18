#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_2__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ClearResults (TYPE_2__*,int) ; 
 int ExecuteOptionalRemoteCommand (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int QUERY_SEND_FAILED ; 
 int RESPONSE_NOT_OKAY ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcontext (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_literal_cstr (char*) ; 

__attribute__((used)) static bool
RecoverPreparedTransactionOnWorker(MultiConnection *connection, char *transactionName,
								   bool shouldCommit)
{
	StringInfo command = makeStringInfo();
	PGresult *result = NULL;
	int executeCommand = 0;
	bool raiseInterrupts = false;

	if (shouldCommit)
	{
		/* should have committed this prepared transaction */
		appendStringInfo(command, "COMMIT PREPARED %s",
						 quote_literal_cstr(transactionName));
	}
	else
	{
		/* should have aborted this prepared transaction */
		appendStringInfo(command, "ROLLBACK PREPARED %s",
						 quote_literal_cstr(transactionName));
	}

	executeCommand = ExecuteOptionalRemoteCommand(connection, command->data, &result);
	if (executeCommand == QUERY_SEND_FAILED)
	{
		return false;
	}
	if (executeCommand == RESPONSE_NOT_OKAY)
	{
		return false;
	}

	PQclear(result);
	ClearResults(connection, raiseInterrupts);

	ereport(LOG, (errmsg("recovered a prepared transaction on %s:%d",
						 connection->hostname, connection->port),
				  errcontext("%s", command->data)));

	return true;
}