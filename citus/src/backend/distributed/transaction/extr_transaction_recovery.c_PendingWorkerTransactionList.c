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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  MultiConnection ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ForgetResults (int /*<<< orphan*/ *) ; 
 int GetLocalGroupId () ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int const) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportConnectionError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportResultError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SendRemoteCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  pstrdup (char*) ; 

__attribute__((used)) static List *
PendingWorkerTransactionList(MultiConnection *connection)
{
	StringInfo command = makeStringInfo();
	bool raiseInterrupts = true;
	int querySent = 0;
	PGresult *result = NULL;
	int rowCount = 0;
	int rowIndex = 0;
	List *transactionNames = NIL;
	int coordinatorId = GetLocalGroupId();

	appendStringInfo(command, "SELECT gid FROM pg_prepared_xacts "
							  "WHERE gid LIKE 'citus\\_%d\\_%%'",
					 coordinatorId);

	querySent = SendRemoteCommand(connection, command->data);
	if (querySent == 0)
	{
		ReportConnectionError(connection, ERROR);
	}

	result = GetRemoteCommandResult(connection, raiseInterrupts);
	if (!IsResponseOK(result))
	{
		ReportResultError(connection, result, ERROR);
	}

	rowCount = PQntuples(result);

	for (rowIndex = 0; rowIndex < rowCount; rowIndex++)
	{
		const int columnIndex = 0;
		char *transactionName = PQgetvalue(result, rowIndex, columnIndex);

		transactionNames = lappend(transactionNames, pstrdup(transactionName));
	}

	PQclear(result);
	ForgetResults(connection);

	return transactionNames;
}