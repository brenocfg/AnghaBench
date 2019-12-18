#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t index; int count; TYPE_2__* connections; } ;
typedef  TYPE_1__ TrackerServerInfo ;
struct TYPE_7__ {scalar_t__ sock; } ;
typedef  TYPE_2__ ConnectionInfo ;

/* Variables and functions */
 int conn_pool_connect_server_ex (TYPE_2__*,int /*<<< orphan*/ ,char const*,int const) ; 
 int /*<<< orphan*/  g_fdfs_connect_timeout ; 

ConnectionInfo *tracker_connect_server_no_pool_ex(TrackerServerInfo *pServerInfo,
        const char *bind_addr, int *err_no, const bool log_connect_error)
{
	ConnectionInfo *conn;
	ConnectionInfo *end;
    int current_index;

	if (pServerInfo->connections[pServerInfo->index].sock >= 0)
	{
        *err_no = 0;
		return pServerInfo->connections + pServerInfo->index;
	}

	*err_no = conn_pool_connect_server_ex(pServerInfo->connections
            + pServerInfo->index, g_fdfs_connect_timeout,
            bind_addr, log_connect_error);
    if (*err_no == 0)
    {
		return pServerInfo->connections + pServerInfo->index;
    }

    if (pServerInfo->count == 1)
    {
        return NULL;
    }

	end = pServerInfo->connections + pServerInfo->count;
	for (conn=pServerInfo->connections; conn<end; conn++)
    {
        current_index = conn - pServerInfo->connections;
        if (current_index != pServerInfo->index)
        {
            if ((*err_no=conn_pool_connect_server_ex(conn,
                            g_fdfs_connect_timeout, bind_addr,
                            log_connect_error)) == 0)
            {
                pServerInfo->index = current_index;
                return pServerInfo->connections + pServerInfo->index;
            }
        }
    }

    return NULL;
}