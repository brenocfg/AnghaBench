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
typedef  size_t int32 ;
struct TYPE_3__ {int /*<<< orphan*/  pgConn; } ;
typedef  int /*<<< orphan*/  ResultStatus ;
typedef  TYPE_1__ MultiConnection ;
typedef  scalar_t__ ConnStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CLIENT_INVALID_RESULT_STATUS ; 
 int /*<<< orphan*/  CLIENT_RESULT_BUSY ; 
 int /*<<< orphan*/  CLIENT_RESULT_READY ; 
 int /*<<< orphan*/  CLIENT_RESULT_UNAVAILABLE ; 
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ CONNECTION_OK ; 
 TYPE_1__** ClientConnectionArray ; 
 size_t INVALID_CONNECTION_ID ; 
 int PQconsumeInput (int /*<<< orphan*/ ) ; 
 int PQisBusy (int /*<<< orphan*/ ) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

ResultStatus
MultiClientResultStatus(int32 connectionId)
{
	MultiConnection *connection = NULL;
	int consumed = 0;
	ConnStatusType connStatusType = CONNECTION_OK;
	ResultStatus resultStatus = CLIENT_INVALID_RESULT_STATUS;

	Assert(connectionId != INVALID_CONNECTION_ID);
	connection = ClientConnectionArray[connectionId];
	Assert(connection != NULL);

	connStatusType = PQstatus(connection->pgConn);
	if (connStatusType == CONNECTION_BAD)
	{
		ereport(WARNING, (errmsg("could not maintain connection to worker node")));
		return CLIENT_RESULT_UNAVAILABLE;
	}

	/* consume input to allow status change */
	consumed = PQconsumeInput(connection->pgConn);
	if (consumed != 0)
	{
		int connectionBusy = PQisBusy(connection->pgConn);
		if (connectionBusy == 0)
		{
			resultStatus = CLIENT_RESULT_READY;
		}
		else
		{
			resultStatus = CLIENT_RESULT_BUSY;
		}
	}
	else
	{
		ereport(WARNING, (errmsg("could not consume data from worker node")));
		resultStatus = CLIENT_RESULT_UNAVAILABLE;
	}

	return resultStatus;
}