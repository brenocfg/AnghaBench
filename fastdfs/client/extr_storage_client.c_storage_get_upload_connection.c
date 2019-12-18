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
struct TYPE_14__ {scalar_t__ sock; } ;
typedef  TYPE_1__ ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CONNECTION (TYPE_1__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (TYPE_1__*,int) ; 
 TYPE_1__* tracker_make_connection (TYPE_1__*,int*) ; 
 int tracker_query_storage_store_with_group (TYPE_1__*,char*,TYPE_1__*,int*) ; 
 int tracker_query_storage_store_without_group (TYPE_1__*,TYPE_1__*,char*,int*) ; 

__attribute__((used)) static int storage_get_upload_connection(ConnectionInfo *pTrackerServer, \
		ConnectionInfo **ppStorageServer, char *group_name, \
		ConnectionInfo *pNewStorage, int *store_path_index, \
		bool *new_connection)
{
	int result;
	bool new_tracker_connection;
	ConnectionInfo *pNewTracker;

	if (*ppStorageServer == NULL)
	{
		CHECK_CONNECTION(pTrackerServer, pNewTracker, result, \
			new_tracker_connection);
		if (*group_name == '\0')
		{
			result = tracker_query_storage_store_without_group( \
				pNewTracker, pNewStorage, group_name, \
				store_path_index);
		}
		else
		{
			result = tracker_query_storage_store_with_group( \
				pNewTracker, group_name, pNewStorage, \
				store_path_index);
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