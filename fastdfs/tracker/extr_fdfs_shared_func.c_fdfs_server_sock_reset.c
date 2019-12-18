#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; TYPE_2__* connections; } ;
typedef  TYPE_1__ TrackerServerInfo ;
struct TYPE_5__ {int sock; } ;
typedef  TYPE_2__ ConnectionInfo ;

/* Variables and functions */

void fdfs_server_sock_reset(TrackerServerInfo *pServerInfo)
{
	ConnectionInfo *conn;
	ConnectionInfo *end;

    if (pServerInfo->count == 1)
    {
		pServerInfo->connections[0].sock = -1;
    }
    else if (pServerInfo->count == 2)
    {
		pServerInfo->connections[0].sock = -1;
		pServerInfo->connections[1].sock = -1;
    }
    else
    {
        end = pServerInfo->connections + pServerInfo->count;
        for (conn=pServerInfo->connections; conn<end; conn++)
        {
            conn->sock = -1;
        }
    }
}