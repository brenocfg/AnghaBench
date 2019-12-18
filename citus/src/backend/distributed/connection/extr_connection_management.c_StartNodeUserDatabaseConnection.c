#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  dlist_head ;
struct TYPE_13__ {int /*<<< orphan*/  connections; } ;
struct TYPE_12__ {int /*<<< orphan*/  database; int /*<<< orphan*/  user; int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; } ;
struct TYPE_11__ {int /*<<< orphan*/  connectionNode; } ;
typedef  TYPE_1__ MultiConnection ;
typedef  TYPE_2__ ConnectionHashKey ;
typedef  TYPE_3__ ConnectionHashEntry ;

/* Variables and functions */
 scalar_t__ COORD_TRANS_IDLE ; 
 scalar_t__ COORD_TRANS_NONE ; 
 int /*<<< orphan*/  ConnectionContext ; 
 int /*<<< orphan*/  ConnectionHash ; 
 scalar_t__ CurrentCoordinatedTransactionState ; 
 char const* CurrentDatabaseName () ; 
 char const* CurrentUserName () ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int FORCE_NEW_CONNECTION ; 
 TYPE_1__* FindAvailableConnection (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 scalar_t__ MAX_NODE_LENGTH ; 
 int /*<<< orphan*/  MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NAMEDATALEN ; 
 int /*<<< orphan*/  ResetShardPlacementAssociation (TYPE_1__*) ; 
 TYPE_1__* StartConnectionEstablishment (TYPE_2__*) ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlist_push_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 
 TYPE_3__* hash_search (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

MultiConnection *
StartNodeUserDatabaseConnection(uint32 flags, const char *hostname, int32 port, const
								char *user, const char *database)
{
	ConnectionHashKey key;
	ConnectionHashEntry *entry = NULL;
	MultiConnection *connection;
	bool found;

	/* do some minimal input checks */
	strlcpy(key.hostname, hostname, MAX_NODE_LENGTH);
	if (strlen(hostname) > MAX_NODE_LENGTH)
	{
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("hostname exceeds the maximum length of %d",
							   MAX_NODE_LENGTH)));
	}

	key.port = port;
	if (user)
	{
		strlcpy(key.user, user, NAMEDATALEN);
	}
	else
	{
		strlcpy(key.user, CurrentUserName(), NAMEDATALEN);
	}
	if (database)
	{
		strlcpy(key.database, database, NAMEDATALEN);
	}
	else
	{
		strlcpy(key.database, CurrentDatabaseName(), NAMEDATALEN);
	}

	if (CurrentCoordinatedTransactionState == COORD_TRANS_NONE)
	{
		CurrentCoordinatedTransactionState = COORD_TRANS_IDLE;
	}

	/*
	 * Lookup relevant hash entry. We always enter. If only a cached
	 * connection is desired, and there's none, we'll simply leave the
	 * connection list empty.
	 */

	entry = hash_search(ConnectionHash, &key, HASH_ENTER, &found);
	if (!found)
	{
		entry->connections = MemoryContextAlloc(ConnectionContext,
												sizeof(dlist_head));
		dlist_init(entry->connections);
	}

	/* if desired, check whether there's a usable connection */
	if (!(flags & FORCE_NEW_CONNECTION))
	{
		/* check connection cache for a connection that's not already in use */
		connection = FindAvailableConnection(entry->connections, flags);
		if (connection)
		{
			return connection;
		}
	}

	/*
	 * Either no caching desired, or no pre-established, non-claimed,
	 * connection present. Initiate connection establishment.
	 */
	connection = StartConnectionEstablishment(&key);

	dlist_push_tail(entry->connections, &connection->connectionNode);

	ResetShardPlacementAssociation(connection);

	return connection;
}