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
struct TYPE_6__ {int /*<<< orphan*/  pgConn; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/ * GetRemoteCommandResult (TYPE_1__*,int) ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MarkRemoteTransactionFailed (TYPE_1__*,int) ; 
 scalar_t__ PGRES_COPY_IN ; 
 scalar_t__ PGRES_FATAL_ERROR ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQputCopyEnd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportResultError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 

__attribute__((used)) static bool
ClearResultsInternal(MultiConnection *connection, bool raiseErrors, bool discardWarnings)
{
	bool success = true;

	while (true)
	{
		PGresult *result = GetRemoteCommandResult(connection, raiseErrors);
		if (result == NULL)
		{
			break;
		}

		/*
		 * End any pending copy operation. Transaction will be marked
		 * as failed by the following part.
		 */
		if (PQresultStatus(result) == PGRES_COPY_IN)
		{
			PQputCopyEnd(connection->pgConn, NULL);
		}

		if (!IsResponseOK(result))
		{
			if (!discardWarnings)
			{
				ReportResultError(connection, result, WARNING);
			}

			MarkRemoteTransactionFailed(connection, raiseErrors);

			success = false;

			/* an error happened, there is nothing we can do more */
			if (PQresultStatus(result) == PGRES_FATAL_ERROR)
			{
				PQclear(result);

				break;
			}
		}

		PQclear(result);
	}

	return success;
}