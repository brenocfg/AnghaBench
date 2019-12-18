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
struct TYPE_4__ {scalar_t__ server_count; int /*<<< orphan*/ * servers; } ;
typedef  TYPE_1__ TrackerServerGroup ;

/* Variables and functions */
 int /*<<< orphan*/  fdfs_server_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool fdfs_tracker_group_equals(TrackerServerGroup *pGroup1,
        TrackerServerGroup *pGroup2)
{
    TrackerServerInfo *pServer1;
    TrackerServerInfo *pServer2;
    TrackerServerInfo *pEnd1;

    if (pGroup1->server_count != pGroup2->server_count)
    {
        return false;
    }

    pEnd1 = pGroup1->servers + pGroup1->server_count;
    pServer1 = pGroup1->servers;
    pServer2 = pGroup2->servers;
    while (pServer1 < pEnd1)
    {
        if (!fdfs_server_equal(pServer1, pServer2))
        {
            return false;
        }

        pServer1++;
        pServer2++;
    }

    return true;
}