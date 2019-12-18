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
struct TYPE_5__ {int /*<<< orphan*/  count; int /*<<< orphan*/  maps; } ;
struct TYPE_4__ {char const* ip_addr; int port; int /*<<< orphan*/ * idInfo; int /*<<< orphan*/ * group_name; } ;
typedef  TYPE_1__ FDFSStorageIdMap ;
typedef  int /*<<< orphan*/  FDFSStorageIdInfo ;

/* Variables and functions */
 scalar_t__ bsearch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdfs_cmp_ip_and_port ; 
 TYPE_2__ g_storage_ids_by_ip_port ; 

FDFSStorageIdInfo *fdfs_get_storage_id_by_ip_port(const char *pIpAddr,
        const int port)
{
	FDFSStorageIdMap target;
	FDFSStorageIdMap *pFound;
    int ports[2];
    int i;

	target.ip_addr = pIpAddr;
	target.group_name = NULL;
    target.idInfo = NULL;
    ports[0] = port;
    ports[1] = 0;
    for (i=0; i<2; i++)
    {
        target.port = ports[i];
        pFound = (FDFSStorageIdMap *)bsearch(&target,
                g_storage_ids_by_ip_port.maps,
                g_storage_ids_by_ip_port.count,
                sizeof(FDFSStorageIdMap), fdfs_cmp_ip_and_port);
        if (pFound != NULL)
        {
            return pFound->idInfo;
        }
    }

    return NULL;
}