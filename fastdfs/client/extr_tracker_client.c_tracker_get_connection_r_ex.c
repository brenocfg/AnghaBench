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
typedef  int /*<<< orphan*/  TrackerServerInfo ;
struct TYPE_3__ {int server_index; int server_count; int /*<<< orphan*/ * servers; } ;
typedef  TYPE_1__ TrackerServerGroup ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  fdfs_server_sock_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tracker_connect_server (int /*<<< orphan*/ *,int*) ; 

ConnectionInfo *tracker_get_connection_r_ex(TrackerServerGroup *pTrackerGroup,
		TrackerServerInfo *pTrackerServer, int *err_no)
{
	ConnectionInfo *conn;
	TrackerServerInfo *pCurrentServer;
	TrackerServerInfo *pServer;
	TrackerServerInfo *pEnd;
	int server_index;

	server_index = pTrackerGroup->server_index;
	if (server_index >= pTrackerGroup->server_count)
	{
		server_index = 0;
	}

	do
	{
	pCurrentServer = pTrackerGroup->servers + server_index;
	memcpy(pTrackerServer, pCurrentServer, sizeof(TrackerServerInfo));
    fdfs_server_sock_reset(pTrackerServer);
	if ((conn=tracker_connect_server(pTrackerServer, err_no)) != NULL)
	{
		break;
	}

	pEnd = pTrackerGroup->servers + pTrackerGroup->server_count;
	for (pServer=pCurrentServer+1; pServer<pEnd; pServer++)
	{
		memcpy(pTrackerServer, pServer, sizeof(TrackerServerInfo));
        fdfs_server_sock_reset(pTrackerServer);
		if ((conn=tracker_connect_server(pTrackerServer, err_no)) != NULL)
		{
			pTrackerGroup->server_index = pServer -
							pTrackerGroup->servers;
			break;
		}
	}

	if (conn != NULL)
	{
		break;
	}

	for (pServer=pTrackerGroup->servers; pServer<pCurrentServer; pServer++)
	{
		memcpy(pTrackerServer, pServer, sizeof(TrackerServerInfo));
        fdfs_server_sock_reset(pTrackerServer);
		if ((conn=tracker_connect_server(pTrackerServer, err_no)) != NULL)
		{
			pTrackerGroup->server_index = pServer -
							pTrackerGroup->servers;
			break;
		}
	}
	} while (0);

	pTrackerGroup->server_index++;
	if (pTrackerGroup->server_index >= pTrackerGroup->server_count)
	{
		pTrackerGroup->server_index = 0;
	}

	return conn;
}