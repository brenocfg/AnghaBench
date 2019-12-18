#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TrackerServerInfo ;
struct TYPE_4__ {int /*<<< orphan*/  server_count; int /*<<< orphan*/  servers; } ;
typedef  TYPE_1__ TrackerServerGroup ;

/* Variables and functions */
 int /*<<< orphan*/  FDFS_TRACKER_SERVER_DEF_PORT ; 
 int /*<<< orphan*/ * bsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int fdfs_parse_server_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdfs_server_sock_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_into_sorted_servers (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  storage_cmp_server_info ; 

__attribute__((used)) static int copy_tracker_servers(TrackerServerGroup *pTrackerGroup,
		const char *filename, char **ppTrackerServers)
{
	char **ppSrc;
	char **ppEnd;
	TrackerServerInfo destServer;
    int result;

	memset(&destServer, 0, sizeof(TrackerServerInfo));
    fdfs_server_sock_reset(&destServer);

	ppEnd = ppTrackerServers + pTrackerGroup->server_count;
	pTrackerGroup->server_count = 0;
	for (ppSrc=ppTrackerServers; ppSrc<ppEnd; ppSrc++)
	{
        if ((result=fdfs_parse_server_info(*ppSrc,
                        FDFS_TRACKER_SERVER_DEF_PORT, &destServer)) != 0)
        {
            return result;
        }

		if (bsearch(&destServer, pTrackerGroup->servers,
			pTrackerGroup->server_count,
			sizeof(TrackerServerInfo),
			storage_cmp_server_info) == NULL)
		{
			insert_into_sorted_servers(pTrackerGroup, &destServer);
			pTrackerGroup->server_count++;
		}
	}

	/*
	{
	TrackerServerInfo *pServer;
	for (pServer=pTrackerGroup->servers; pServer<pTrackerGroup->servers+ \
		pTrackerGroup->server_count;	pServer++)
	{
		//printf("server=%s:%d\n", \
			pServer->ip_addr, pServer->port);
	}
	}
	*/

	return 0;
}