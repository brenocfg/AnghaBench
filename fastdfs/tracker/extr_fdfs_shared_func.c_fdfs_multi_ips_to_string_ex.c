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
struct TYPE_4__ {char* address; } ;
typedef  TYPE_2__ FDFSMultiIP ;

/* Variables and functions */
 int snprintf (char*,int const,char*,...) ; 

int fdfs_multi_ips_to_string_ex(const FDFSMultiIP *ip_addrs,
        const char seperator, char *buff, const int buffSize)
{
    int i;
    int len;

    if (ip_addrs->count <= 0)
    {
        *buff = '\0';
        return 0;
    }
    if (ip_addrs->count == 1)
    {
        return snprintf(buff, buffSize, "%s",
                ip_addrs->ips[0].address);
    }

    len = snprintf(buff, buffSize, "%s", ip_addrs->ips[0].address);
	for (i=1; i<ip_addrs->count; i++)
    {
        len += snprintf(buff + len, buffSize - len, "%c%s",
                seperator, ip_addrs->ips[i].address);
    }
    return len;
}