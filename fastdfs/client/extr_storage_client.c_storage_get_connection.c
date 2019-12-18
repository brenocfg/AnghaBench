#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ byte ;
struct TYPE_14__ {scalar_t__ sock; } ;
typedef  TYPE_1__ ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CONNECTION (TYPE_1__*,TYPE_1__*,int,int) ; 
 scalar_t__ const TRACKER_PROTO_CMD_SERVICE_QUERY_FETCH_ONE ; 
 int /*<<< orphan*/  tracker_close_connection_ex (TYPE_1__*,int) ; 
 TYPE_1__* tracker_make_connection (TYPE_1__*,int*) ; 
 int tracker_query_storage_fetch (TYPE_1__*,TYPE_1__*,char const*,char const*) ; 
 int tracker_query_storage_update (TYPE_1__*,TYPE_1__*,char const*,char const*) ; 

__attribute__((used)) static int storage_get_connection(ConnectionInfo *pTrackerServer, \
		ConnectionInfo **ppStorageServer, const byte cmd, \
		const char *group_name, const char *filename, \
		ConnectionInfo *pNewStorage, bool *new_connection)
{
	int result;
	bool new_tracker_connection;
	ConnectionInfo *pNewTracker;
	if (*ppStorageServer == NULL)
	{
		CHECK_CONNECTION(pTrackerServer, pNewTracker, result, \
			new_tracker_connection);
		if (cmd == TRACKER_PROTO_CMD_SERVICE_QUERY_FETCH_ONE)
		{
			result = tracker_query_storage_fetch(pNewTracker, \
		                pNewStorage, group_name, filename);
		}
		else
		{
			result = tracker_query_storage_update(pNewTracker, \
		                pNewStorage, group_name, filename);
		}

		if (new_tracker_connection)
		{
			tracker_close_connection_ex(pNewTracker, result != 0);
		}

		if (result != 0)
		{
			return result;
		}

		if ((*ppStorageServer=tracker_make_connection(pNewStorage,
			&result)) == NULL)
		{
			return result;
		}

		*new_connection = true;
	}
	else
	{
		if ((*ppStorageServer)->sock >= 0)
		{
			*new_connection = false;
		}
		else
		{
			if ((*ppStorageServer=tracker_make_connection(
				*ppStorageServer, &result)) == NULL)
			{
				return result;
			}

			*new_connection = true;
		}
	}

	return 0;
}