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
struct TYPE_5__ {int count; TYPE_1__* ips; } ;
struct TYPE_4__ {char const* address; int type; } ;
typedef  TYPE_2__ FDFSMultiIP ;

/* Variables and functions */
 size_t FDFS_MULTI_IP_INDEX_INNER ; 
 size_t FDFS_MULTI_IP_INDEX_OUTER ; 
 int fdfs_get_ip_type (char const*) ; 

const char *fdfs_get_ipaddr_by_peer_ip(const FDFSMultiIP *ip_addrs,
        const char *client_ip)
{
    int ip_type;
    int index;
    if (ip_addrs->count == 1)
    {
        return ip_addrs->ips[0].address;
    }

    if (ip_addrs->count <= 0)
    {
        return "";
    }

    ip_type = fdfs_get_ip_type(client_ip);
    index = ip_addrs->ips[FDFS_MULTI_IP_INDEX_OUTER].type == ip_type ?
        FDFS_MULTI_IP_INDEX_OUTER : FDFS_MULTI_IP_INDEX_INNER;
    return ip_addrs->ips[index].address;
}