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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ForgetResults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int QUERY_SEND_FAILED ; 
 int RESPONSE_NOT_OKAY ; 
 int RESPONSE_OKAY ; 
 int /*<<< orphan*/  ReportConnectionError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportResultError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SendRemoteCommand (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  WARNING ; 

int
ExecuteOptionalRemoteCommand(MultiConnection *connection, const char *command,
							 PGresult **result)
{
	int querySent = 0;
	PGresult *localResult = NULL;
	bool raiseInterrupts = true;

	querySent = SendRemoteCommand(connection, command);
	if (querySent == 0)
	{
		ReportConnectionError(connection, WARNING);
		return QUERY_SEND_FAILED;
	}

	localResult = GetRemoteCommandResult(connection, raiseInterrupts);
	if (!IsResponseOK(localResult))
	{
		ReportResultError(connection, localResult, WARNING);
		PQclear(localResult);
		ForgetResults(connection);
		return RESPONSE_NOT_OKAY;
	}

	/*
	 * store result if result has been set, when the user is not interested in the result
	 * a NULL pointer could be passed and the result will be cleared.
	 */
	if (result != NULL)
	{
		*result = localResult;
	}
	else
	{
		PQclear(localResult);
		ForgetResults(connection);
	}

	return RESPONSE_OKAY;
}