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
typedef  int /*<<< orphan*/  WaitEventSet ;
struct TYPE_3__ {int /*<<< orphan*/  pgConn; } ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  AddWaitEventToSet (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * CreateWaitEventSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/ * MyLatch ; 
 int PGINVALID_SOCKET ; 
 int PQsocket (int /*<<< orphan*/ ) ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WL_SOCKET_READABLE ; 
 int WL_SOCKET_WRITEABLE ; 

__attribute__((used)) static WaitEventSet *
BuildWaitEventSet(MultiConnection **allConnections, int totalConnectionCount,
				  int pendingConnectionsStartIndex)
{
	int pendingConnectionCount = totalConnectionCount - pendingConnectionsStartIndex;
	WaitEventSet *waitEventSet = NULL;
	int connectionIndex = 0;

	/*
	 * subtract 3 to make room for WL_POSTMASTER_DEATH, WL_LATCH_SET, and
	 * pgwin32_signal_event.
	 */
	if (pendingConnectionCount > FD_SETSIZE - 3)
	{
		pendingConnectionCount = FD_SETSIZE - 3;
	}

	/* allocate pending connections + 2 for the signal latch and postmaster death */
	/* (CreateWaitEventSet makes room for pgwin32_signal_event automatically) */
	waitEventSet = CreateWaitEventSet(CurrentMemoryContext, pendingConnectionCount + 2);

	for (connectionIndex = 0; connectionIndex < pendingConnectionCount; connectionIndex++)
	{
		MultiConnection *connection = allConnections[pendingConnectionsStartIndex +
													 connectionIndex];
		int sock = PQsocket(connection->pgConn);

		/*
		 * Always start by polling for both readability (server sent bytes)
		 * and writeability (server is ready to receive bytes).
		 */
		int eventMask = WL_SOCKET_READABLE | WL_SOCKET_WRITEABLE;

		AddWaitEventToSet(waitEventSet, eventMask, sock, NULL, (void *) connection);
	}

	/*
	 * Put the wait events for the signal latch and postmaster death at the end such that
	 * event index + pendingConnectionsStartIndex = the connection index in the array.
	 */
	AddWaitEventToSet(waitEventSet, WL_POSTMASTER_DEATH, PGINVALID_SOCKET, NULL, NULL);
	AddWaitEventToSet(waitEventSet, WL_LATCH_SET, PGINVALID_SOCKET, MyLatch, NULL);

	return waitEventSet;
}