#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  conn_pool_disconnect_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdfs_client_destroy () ; 
 int /*<<< orphan*/  pTrackerServer ; 
 int storage_server_count ; 
 int /*<<< orphan*/ * storage_servers ; 
 int /*<<< orphan*/  tracker_close_connection (int /*<<< orphan*/ ) ; 

void dfs_destroy()
{
	ConnectionInfo *pEnd;
	ConnectionInfo *pServer;

	tracker_close_connection(pTrackerServer);

	pEnd = storage_servers + storage_server_count;
	for (pServer=storage_servers; pServer<pEnd; pServer++)
	{
		conn_pool_disconnect_server(pServer);
	}

	fdfs_client_destroy();
}