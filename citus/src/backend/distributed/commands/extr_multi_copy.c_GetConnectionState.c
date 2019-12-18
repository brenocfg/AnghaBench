#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int socket; int /*<<< orphan*/  bufferedPlacementList; int /*<<< orphan*/ * activePlacementState; TYPE_1__* connection; } ;
struct TYPE_5__ {int /*<<< orphan*/  pgConn; } ;
typedef  TYPE_1__ MultiConnection ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_2__ CopyConnectionState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int PQsocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static CopyConnectionState *
GetConnectionState(HTAB *connectionStateHash, MultiConnection *connection)
{
	CopyConnectionState *connectionState = NULL;
	bool found = false;

	int sock = PQsocket(connection->pgConn);
	Assert(sock != -1);

	connectionState = (CopyConnectionState *) hash_search(connectionStateHash, &sock,
														  HASH_ENTER, &found);
	if (!found)
	{
		connectionState->socket = sock;
		connectionState->connection = connection;
		connectionState->activePlacementState = NULL;
		dlist_init(&connectionState->bufferedPlacementList);
	}

	return connectionState;
}