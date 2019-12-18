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
typedef  int uint64 ;
typedef  size_t int32 ;
struct TYPE_7__ {int /*<<< orphan*/  pgConn; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ MultiConnection ;
typedef  scalar_t__ ExecStatusType ;
typedef  int /*<<< orphan*/  CopyStatus ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CLIENT_COPY_DONE ; 
 int /*<<< orphan*/  CLIENT_COPY_FAILED ; 
 int /*<<< orphan*/  CLIENT_COPY_MORE ; 
 int /*<<< orphan*/  CLIENT_INVALID_COPY ; 
 TYPE_1__** ClientConnectionArray ; 
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  ForgetResults (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (TYPE_1__*,int) ; 
 size_t INVALID_CONNECTION_ID ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQconsumeInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int PQgetCopyData (int /*<<< orphan*/ ,char**,int const) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportConnectionError (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportResultError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ errno ; 
 int write (size_t,char*,int) ; 

CopyStatus
MultiClientCopyData(int32 connectionId, int32 fileDescriptor, uint64 *returnBytesReceived)
{
	MultiConnection *connection = NULL;
	char *receiveBuffer = NULL;
	int consumed = 0;
	int receiveLength = 0;
	const int asynchronous = 1;
	CopyStatus copyStatus = CLIENT_INVALID_COPY;

	Assert(connectionId != INVALID_CONNECTION_ID);
	connection = ClientConnectionArray[connectionId];
	Assert(connection != NULL);

	/*
	 * Consume input to handle the case where previous copy operation might have
	 * received zero bytes.
	 */
	consumed = PQconsumeInput(connection->pgConn);
	if (consumed == 0)
	{
		ereport(WARNING, (errmsg("could not read data from worker node")));
		return CLIENT_COPY_FAILED;
	}

	/* receive copy data message in an asynchronous manner */
	receiveLength = PQgetCopyData(connection->pgConn, &receiveBuffer, asynchronous);
	while (receiveLength > 0)
	{
		/* received copy data; append these data to file */
		int appended = -1;
		errno = 0;

		if (returnBytesReceived)
		{
			*returnBytesReceived += receiveLength;
		}

		appended = write(fileDescriptor, receiveBuffer, receiveLength);
		if (appended != receiveLength)
		{
			/* if write didn't set errno, assume problem is no disk space */
			if (errno == 0)
			{
				errno = ENOSPC;
			}
			ereport(FATAL, (errcode_for_file_access(),
							errmsg("could not append to copied file: %m")));
		}

		PQfreemem(receiveBuffer);

		receiveLength = PQgetCopyData(connection->pgConn, &receiveBuffer, asynchronous);
	}

	/* we now check the last received length returned by copy data */
	if (receiveLength == 0)
	{
		/* we cannot read more data without blocking */
		copyStatus = CLIENT_COPY_MORE;
	}
	else if (receiveLength == -1)
	{
		/* received copy done message */
		bool raiseInterrupts = true;
		PGresult *result = GetRemoteCommandResult(connection, raiseInterrupts);
		ExecStatusType resultStatus = PQresultStatus(result);

		if (resultStatus == PGRES_COMMAND_OK)
		{
			copyStatus = CLIENT_COPY_DONE;
		}
		else
		{
			copyStatus = CLIENT_COPY_FAILED;

			ReportResultError(connection, result, WARNING);
		}

		PQclear(result);
	}
	else if (receiveLength == -2)
	{
		/* received an error */
		copyStatus = CLIENT_COPY_FAILED;

		ReportConnectionError(connection, WARNING);
	}

	/* if copy out completed, make sure we drain all results from libpq */
	if (receiveLength < 0)
	{
		ForgetResults(connection);
	}

	return copyStatus;
}