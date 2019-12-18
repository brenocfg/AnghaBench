#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TrackerServerInfo ;
struct TYPE_6__ {int server_count; int /*<<< orphan*/ * servers; } ;
typedef  TYPE_1__ TrackerServerGroup ;
struct TYPE_7__ {int status; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ FDFSStorageBrief ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  fdfs_server_sock_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tracker_connect_server (int /*<<< orphan*/ *,int*) ; 
 int tracker_get_storage_status (int /*<<< orphan*/ *,char const*,char const*,TYPE_2__*) ; 

int tracker_get_storage_max_status(TrackerServerGroup *pTrackerGroup, \
		const char *group_name, const char *ip_addr, \
		char *storage_id, int *status)
{
	ConnectionInfo *conn;
	TrackerServerInfo tracker_server;
	TrackerServerInfo *pServer;
	TrackerServerInfo *pEnd;
	FDFSStorageBrief storage_brief;
	int result;

	memset(&storage_brief, 0, sizeof(FDFSStorageBrief));
	storage_brief.status = -1;

	*storage_id = '\0';
	*status = -1;
	pEnd = pTrackerGroup->servers + pTrackerGroup->server_count;
	for (pServer=pTrackerGroup->servers; pServer<pEnd; pServer++)
	{
		memcpy(&tracker_server, pServer, sizeof(TrackerServerInfo));
        fdfs_server_sock_reset(&tracker_server);
		if ((conn=tracker_connect_server(&tracker_server, &result)) == NULL)
		{
			return result;
		}

		result = tracker_get_storage_status(conn, group_name, \
				ip_addr, &storage_brief);
		tracker_close_connection_ex(conn, result != 0);

		if (result != 0)
		{
			if (result == ENOENT)
			{
				continue;
			}
			return result;
		}

		strcpy(storage_id, storage_brief.id);
		if (storage_brief.status > *status)
		{
			*status = storage_brief.status;
		}
	}

	if (*status == -1)
	{
		return ENOENT;
	}

	return 0;
}