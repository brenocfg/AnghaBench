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
struct TYPE_3__ {int count; int /*<<< orphan*/ * connections; } ;
typedef  TYPE_1__ TrackerServerInfo ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  tracker_close_connection_ex (int /*<<< orphan*/ *,int) ; 

void tracker_disconnect_server(TrackerServerInfo *pServerInfo)
{
	ConnectionInfo *conn;
	ConnectionInfo *end;

    if (pServerInfo->count == 1)
    {
        tracker_close_connection_ex(pServerInfo->connections + 0, true);
        return;
    }

	end = pServerInfo->connections + pServerInfo->count;
	for (conn=pServerInfo->connections; conn<end; conn++)
    {
        tracker_close_connection_ex(conn, true);
    }
}