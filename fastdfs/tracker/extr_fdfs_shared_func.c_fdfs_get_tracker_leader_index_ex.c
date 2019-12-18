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
struct TYPE_3__ {scalar_t__ server_count; int /*<<< orphan*/ * servers; } ;
typedef  TYPE_1__ TrackerServerGroup ;

/* Variables and functions */
 scalar_t__ fdfs_server_contain (int /*<<< orphan*/ *,char const*,int const) ; 

int fdfs_get_tracker_leader_index_ex(TrackerServerGroup *pServerGroup,
		const char *leaderIp, const int leaderPort)
{
	TrackerServerInfo *pServer;
	TrackerServerInfo *pEnd;

	if (pServerGroup->server_count == 0)
	{
		return -1;
	}

	pEnd = pServerGroup->servers + pServerGroup->server_count;
	for (pServer=pServerGroup->servers; pServer<pEnd; pServer++)
	{
        if (fdfs_server_contain(pServer, leaderIp, leaderPort))
		{
			return pServer - pServerGroup->servers;
		}
	}

	return -1;
}