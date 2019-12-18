#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pgConn; } ;
struct TYPE_4__ {scalar_t__ phase; int /*<<< orphan*/  pollmode; TYPE_2__* connection; } ;
typedef  int /*<<< orphan*/  PostgresPollingStatusType ;
typedef  TYPE_1__ MultiConnectionPollState ;
typedef  TYPE_2__ MultiConnection ;
typedef  scalar_t__ ConnStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ CONNECTION_OK ; 
 void* MULTI_CONNECTION_PHASE_CONNECTED ; 
 scalar_t__ MULTI_CONNECTION_PHASE_CONNECTING ; 
 void* MULTI_CONNECTION_PHASE_ERROR ; 
 int /*<<< orphan*/  PGRES_POLLING_FAILED ; 
 int /*<<< orphan*/  PGRES_POLLING_OK ; 
 int /*<<< orphan*/  PGRES_POLLING_READING ; 
 int /*<<< orphan*/  PGRES_POLLING_WRITING ; 
 int /*<<< orphan*/  PQconnectPoll (int /*<<< orphan*/ ) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
MultiConnectionStatePoll(MultiConnectionPollState *connectionState)
{
	MultiConnection *connection = connectionState->connection;
	ConnStatusType status = PQstatus(connection->pgConn);
	PostgresPollingStatusType oldPollmode = connectionState->pollmode;

	Assert(connectionState->phase == MULTI_CONNECTION_PHASE_CONNECTING);

	if (status == CONNECTION_OK)
	{
		connectionState->phase = MULTI_CONNECTION_PHASE_CONNECTED;
		return true;
	}
	else if (status == CONNECTION_BAD)
	{
		/* FIXME: retries? */
		connectionState->phase = MULTI_CONNECTION_PHASE_ERROR;
		return true;
	}
	else
	{
		connectionState->phase = MULTI_CONNECTION_PHASE_CONNECTING;
	}

	connectionState->pollmode = PQconnectPoll(connection->pgConn);

	/*
	 * FIXME: Do we want to add transparent retry support here?
	 */
	if (connectionState->pollmode == PGRES_POLLING_FAILED)
	{
		connectionState->phase = MULTI_CONNECTION_PHASE_ERROR;
		return true;
	}
	else if (connectionState->pollmode == PGRES_POLLING_OK)
	{
		connectionState->phase = MULTI_CONNECTION_PHASE_CONNECTED;
		return true;
	}
	else
	{
		Assert(connectionState->pollmode == PGRES_POLLING_WRITING ||
			   connectionState->pollmode == PGRES_POLLING_READING);
	}

	return (oldPollmode != connectionState->pollmode) ? true : false;
}