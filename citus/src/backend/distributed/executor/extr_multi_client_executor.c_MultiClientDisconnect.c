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
typedef  size_t int32 ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ ** ClientConnectionArray ; 
 int* ClientPollingStatusArray ; 
 int /*<<< orphan*/  CloseConnection (int /*<<< orphan*/ *) ; 
 size_t INVALID_CONNECTION_ID ; 

void
MultiClientDisconnect(int32 connectionId)
{
	MultiConnection *connection = NULL;
	const int InvalidPollingStatus = -1;

	Assert(connectionId != INVALID_CONNECTION_ID);
	connection = ClientConnectionArray[connectionId];
	Assert(connection != NULL);

	CloseConnection(connection);

	ClientConnectionArray[connectionId] = NULL;
	ClientPollingStatusArray[connectionId] = InvalidPollingStatus;
}