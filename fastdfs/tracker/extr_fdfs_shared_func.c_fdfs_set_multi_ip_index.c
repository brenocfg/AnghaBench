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
struct TYPE_5__ {int count; int index; TYPE_1__* ips; } ;
struct TYPE_4__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ FDFSMultiIP ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

void fdfs_set_multi_ip_index(FDFSMultiIP *multi_ip, const char *target_ip)
{
    int i;
    if (multi_ip->count == 1)
    {
        return;
    }

    for (i=0; i<multi_ip->count; i++)
    {
        if (strcmp(multi_ip->ips[i].address, target_ip) == 0)
        {
            multi_ip->index = i;
            break;
        }
    }
}