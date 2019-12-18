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
struct TYPE_3__ {int server_count; int /*<<< orphan*/ * servers; } ;
typedef  TYPE_1__ TrackerServerGroup ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  fdfs_active_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tracker_connect_server_no_pool (int /*<<< orphan*/ *,int*) ; 

int tracker_get_all_connections_ex(TrackerServerGroup *pTrackerGroup)
{
	TrackerServerInfo *pServer;
	TrackerServerInfo *pEnd;
    ConnectionInfo *conn;
    int result;
	int success_count;

	success_count = 0;
	pEnd = pTrackerGroup->servers + pTrackerGroup->server_count;
	for (pServer=pTrackerGroup->servers; pServer<pEnd; pServer++)
	{
		if ((conn=tracker_connect_server_no_pool(pServer, &result)) != NULL)
		{
			fdfs_active_test(conn);
			success_count++;
		}
	}

	return success_count > 0 ? 0 : ENOTCONN;
}