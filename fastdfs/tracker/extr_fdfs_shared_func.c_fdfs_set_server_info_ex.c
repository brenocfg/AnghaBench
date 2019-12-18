#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int count; scalar_t__ connections; scalar_t__ index; } ;
typedef  TYPE_2__ TrackerServerInfo ;
struct TYPE_8__ {int count; TYPE_1__* ips; } ;
struct TYPE_6__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_3__ FDFSMultiIP ;

/* Variables and functions */
 int /*<<< orphan*/  conn_pool_set_server_info (scalar_t__,int /*<<< orphan*/ ,int const) ; 

void fdfs_set_server_info_ex(TrackerServerInfo *pServer,
        const FDFSMultiIP *ip_addrs, const int port)
{
    int i;

    pServer->count = ip_addrs->count;
    pServer->index = 0;
    for (i=0; i<ip_addrs->count; i++)
    {
        conn_pool_set_server_info(pServer->connections + i,
                ip_addrs->ips[i].address, port);
    }
}