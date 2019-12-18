#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pgConn; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_1__ MultiConnection ;
typedef  scalar_t__ ExecStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_COPY_IN ; 
 scalar_t__ PGRES_COPY_OUT ; 
 scalar_t__ PGRES_SINGLE_TUPLE ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQconsumeInput (int /*<<< orphan*/ *) ; 
 int PQflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 scalar_t__ PQisBusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQisnonblocking (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_unreachable () ; 

bool
ClearResultsIfReady(MultiConnection *connection)
{
	PGconn *pgConn = connection->pgConn;

	if (PQstatus(pgConn) != CONNECTION_OK)
	{
		return false;
	}

	Assert(PQisnonblocking(pgConn));

	while (true)
	{
		PGresult *result = NULL;
		ExecStatusType resultStatus;

		/*
		 * If busy, there might still be results already received and buffered
		 * by the OS. As connection is in non-blocking mode, we can check for
		 * that without blocking.
		 */
		if (PQisBusy(pgConn))
		{
			if (PQflush(pgConn) == -1)
			{
				/* write failed */
				return false;
			}
			if (PQconsumeInput(pgConn) == 0)
			{
				/* some low-level failure */
				return false;
			}
		}

		/* clearing would require blocking IO, return */
		if (PQisBusy(pgConn))
		{
			return false;
		}

		result = PQgetResult(pgConn);
		if (result == NULL)
		{
			/* no more results available */
			return true;
		}

		resultStatus = PQresultStatus(result);

		/* only care about the status, can clear now */
		PQclear(result);

		if (resultStatus == PGRES_COPY_IN || resultStatus == PGRES_COPY_OUT)
		{
			/* in copy, can't reliably recover without blocking */
			return false;
		}

		if (!(resultStatus == PGRES_SINGLE_TUPLE || resultStatus == PGRES_TUPLES_OK ||
			  resultStatus == PGRES_COMMAND_OK))
		{
			/* an error occcurred just when we were aborting */
			return false;
		}

		/* check if there are more results to consume */
	}

	pg_unreachable();
}