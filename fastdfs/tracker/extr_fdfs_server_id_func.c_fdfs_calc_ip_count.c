#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; TYPE_2__* ids; } ;
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_5__ {TYPE_1__ ip_addrs; } ;
typedef  TYPE_2__ FDFSStorageIdInfo ;

/* Variables and functions */
 TYPE_3__ g_storage_ids_by_id ; 

__attribute__((used)) static int fdfs_calc_ip_count()
{
	FDFSStorageIdInfo *idInfo;
	FDFSStorageIdInfo *idEnd;
    int ip_count;

    ip_count = 0;
    idEnd = g_storage_ids_by_id.ids + g_storage_ids_by_id.count;
    for (idInfo=g_storage_ids_by_id.ids; idInfo<idEnd; idInfo++)
    {
        ip_count += idInfo->ip_addrs.count;
    }

    return ip_count;
}