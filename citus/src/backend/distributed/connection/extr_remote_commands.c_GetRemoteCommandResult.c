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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CONNECTION_BAD ; 
 int /*<<< orphan*/  FinishConnectionIO (TYPE_1__*,int) ; 
 int /*<<< orphan*/  PGRES_FATAL_ERROR ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQisBusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQmakeEmptyPGresult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 

PGresult *
GetRemoteCommandResult(MultiConnection *connection, bool raiseInterrupts)
{
	PGconn *pgConn = connection->pgConn;
	PGresult *result = NULL;

	/*
	 * Short circuit tests around the more expensive parts of this
	 * routine. This'd also trigger a return in the, unlikely, case of a
	 * failed/nonexistant connection.
	 */
	if (!PQisBusy(pgConn))
	{
		return PQgetResult(connection->pgConn);
	}

	if (!FinishConnectionIO(connection, raiseInterrupts))
	{
		/* some error(s) happened while doing the I/O, signal the callers */
		if (PQstatus(pgConn) == CONNECTION_BAD)
		{
			return PQmakeEmptyPGresult(pgConn, PGRES_FATAL_ERROR);
		}

		return NULL;
	}

	/* no IO should be necessary to get result */
	Assert(!PQisBusy(pgConn));

	result = PQgetResult(connection->pgConn);

	return result;
}