#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TrackerServerInfo ;
struct TYPE_2__ {int server_count; int /*<<< orphan*/ * servers; } ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  fdfs_server_sock_reset (int /*<<< orphan*/ *) ; 
 TYPE_1__ g_tracker_group ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int storage_do_get_group_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tracker_connect_server (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int storage_get_group_name_from_tracker()
{
	TrackerServerInfo *pTrackerServer;
	TrackerServerInfo *pServerEnd;
	ConnectionInfo *pTrackerConn;
	TrackerServerInfo tracker_server;
	int result;

	result = ENOENT;
	pServerEnd = g_tracker_group.servers + g_tracker_group.server_count;
	for (pTrackerServer=g_tracker_group.servers;
		pTrackerServer<pServerEnd; pTrackerServer++)
	{
		memcpy(&tracker_server, pTrackerServer, sizeof(TrackerServerInfo));
        fdfs_server_sock_reset(&tracker_server);
        if ((pTrackerConn=tracker_connect_server(&tracker_server,
			&result)) == NULL)
		{
			continue;
		}

        result = storage_do_get_group_name(pTrackerConn);
		tracker_close_connection_ex(pTrackerConn,
			result != 0 && result != ENOENT);
		if (result == 0)
		{
			return 0;
		}
	}

	return result;
}