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
struct TYPE_4__ {char const* group_name; char const* ip_addr; int /*<<< orphan*/ * idInfo; scalar_t__ port; } ;
typedef  TYPE_1__ FDFSStorageIdMap ;
typedef  int /*<<< orphan*/  FDFSStorageIdInfo ;

/* Variables and functions */
 scalar_t__ bsearch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdfs_cmp_group_name_and_ip ; 
 TYPE_2__ g_storage_ids_by_ip ; 

FDFSStorageIdInfo *fdfs_get_storage_id_by_ip(const char *group_name,
		const char *pIpAddr)
{
	FDFSStorageIdMap target;
	FDFSStorageIdMap *pFound;

	target.group_name =  group_name;
	target.ip_addr = pIpAddr;
	target.port = 0;
    target.idInfo = NULL;
	pFound = (FDFSStorageIdMap *)bsearch(&target,
            g_storage_ids_by_ip.maps, g_storage_ids_by_ip.count,
            sizeof(FDFSStorageIdMap), fdfs_cmp_group_name_and_ip);
	if (pFound == NULL)
	{
		return NULL;
	}
	else
	{
		return pFound->idInfo;
	}
}