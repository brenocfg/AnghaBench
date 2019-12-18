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
struct TYPE_3__ {int count; scalar_t__ connections; scalar_t__ index; } ;
typedef  TYPE_1__ TrackerServerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  conn_pool_set_server_info (scalar_t__,char const*,int const) ; 

void fdfs_set_server_info(TrackerServerInfo *pServer,
        const char *ip_addr, const int port)
{
    pServer->count = 1;
    pServer->index = 0;
    conn_pool_set_server_info(pServer->connections + 0, ip_addr, port);
}