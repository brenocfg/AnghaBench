#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  database; int /*<<< orphan*/  user; int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; } ;
struct TYPE_8__ {int /*<<< orphan*/  connectionNode; int /*<<< orphan*/  database; int /*<<< orphan*/  user; int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; int /*<<< orphan*/ * pgConn; } ;
typedef  TYPE_1__ MultiConnection ;
typedef  TYPE_2__ ConnectionHashKey ;

/* Variables and functions */
 int /*<<< orphan*/  CloseRemoteTransaction (TYPE_1__*) ; 
 int /*<<< orphan*/  CloseShardPlacementAssociation (TYPE_1__*) ; 
 int /*<<< orphan*/  ConnectionHash ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  MAX_NODE_LENGTH ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
CloseConnection(MultiConnection *connection)
{
	ConnectionHashKey key;
	bool found;

	/* close connection */
	PQfinish(connection->pgConn);
	connection->pgConn = NULL;

	strlcpy(key.hostname, connection->hostname, MAX_NODE_LENGTH);
	key.port = connection->port;
	strlcpy(key.user, connection->user, NAMEDATALEN);
	strlcpy(key.database, connection->database, NAMEDATALEN);

	hash_search(ConnectionHash, &key, HASH_FIND, &found);

	if (found)
	{
		/* unlink from list of open connections */
		dlist_delete(&connection->connectionNode);

		/* same for transaction state and shard/placement machinery */
		CloseRemoteTransaction(connection);
		CloseShardPlacementAssociation(connection);

		/* we leave the per-host entry alive */
		pfree(connection);
	}
	else
	{
		ereport(ERROR, (errmsg("closing untracked connection")));
	}
}