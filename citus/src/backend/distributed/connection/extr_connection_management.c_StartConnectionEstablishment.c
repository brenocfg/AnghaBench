#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int isValid; scalar_t__ values; scalar_t__ keywords; int /*<<< orphan*/  runtimeParamStart; } ;
struct TYPE_13__ {int /*<<< orphan*/  user; int /*<<< orphan*/  database; int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; } ;
struct TYPE_12__ {int /*<<< orphan*/  pgConn; int /*<<< orphan*/  connectionStart; int /*<<< orphan*/  user; int /*<<< orphan*/  database; int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ MultiConnection ;
typedef  TYPE_2__ ConnectionHashKey ;
typedef  TYPE_3__ ConnParamsHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ConnParamsHash ; 
 int /*<<< orphan*/  ConnectionContext ; 
 int /*<<< orphan*/  FreeConnParamsHashEntryFields (TYPE_3__*) ; 
 int /*<<< orphan*/  GetConnParams (TYPE_2__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  MAX_NODE_LENGTH ; 
 TYPE_1__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  PQconnectStartParams (char const**,char const**,int) ; 
 int /*<<< orphan*/  PQsetnonblocking (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetCitusNoticeProcessor (TYPE_1__*) ; 
 TYPE_3__* hash_search (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MultiConnection *
StartConnectionEstablishment(ConnectionHashKey *key)
{
	bool found = false;
	MultiConnection *connection = NULL;
	ConnParamsHashEntry *entry = NULL;

	/* search our cache for precomputed connection settings */
	entry = hash_search(ConnParamsHash, key, HASH_ENTER, &found);
	if (!found || !entry->isValid)
	{
		/* avoid leaking memory in the keys and values arrays */
		if (found && !entry->isValid)
		{
			FreeConnParamsHashEntryFields(entry);
		}

		/* if not found or not valid, compute them from GUC, runtime, etc. */
		GetConnParams(key, &entry->keywords, &entry->values, &entry->runtimeParamStart,
					  ConnectionContext);

		entry->isValid = true;
	}

	connection = MemoryContextAllocZero(ConnectionContext, sizeof(MultiConnection));

	strlcpy(connection->hostname, key->hostname, MAX_NODE_LENGTH);
	connection->port = key->port;
	strlcpy(connection->database, key->database, NAMEDATALEN);
	strlcpy(connection->user, key->user, NAMEDATALEN);


	connection->pgConn = PQconnectStartParams((const char **) entry->keywords,
											  (const char **) entry->values,
											  false);
	connection->connectionStart = GetCurrentTimestamp();

	/*
	 * To avoid issues with interrupts not getting caught all our connections
	 * are managed in a non-blocking manner. remote_commands.c provides
	 * wrappers emulating blocking behaviour.
	 */
	PQsetnonblocking(connection->pgConn, true);

	SetCitusNoticeProcessor(connection);

	return connection;
}