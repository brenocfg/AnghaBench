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

/* Variables and functions */
 scalar_t__ fdfs_server_contain (int /*<<< orphan*/ *,char const*,int const) ; 

TrackerServerInfo *fdfs_tracker_group_get_server(TrackerServerGroup *pGroup,
        const char *target_ip, const int target_port)
{
    TrackerServerInfo *pServer;
    TrackerServerInfo *pEnd;

    pEnd = pGroup->servers + pGroup->server_count;
    for (pServer=pGroup->servers; pServer<pEnd; pServer++)
    {
        if (fdfs_server_contain(pServer, target_ip, target_port))
        {
            return pServer;
        }
    }

    return NULL;
}