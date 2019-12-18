#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int count; TYPE_2__* connections; } ;
typedef  TYPE_1__ TrackerServerInfo ;
struct TYPE_8__ {scalar_t__ port; int /*<<< orphan*/  ip_addr; } ;
typedef  TYPE_2__ ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  fdfs_server_contain1 (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool fdfs_server_equal(TrackerServerInfo *pServer1,
        TrackerServerInfo *pServer2)
{
	ConnectionInfo *conn;
	ConnectionInfo *end;

    if (pServer1->count != pServer2->count)
    {
        return false;
    }

    if (pServer1->count == 1)
    {
        return (pServer1->connections->port == pServer2->connections->port &&
            strcmp(pServer1->connections->ip_addr, pServer2->connections->ip_addr) == 0);
    }

	end = pServer1->connections + pServer1->count;
	for (conn=pServer1->connections; conn<end; conn++)
    {
		if (!fdfs_server_contain1(pServer2, conn))
        {
            return false;
        }
    }

    return true;
}