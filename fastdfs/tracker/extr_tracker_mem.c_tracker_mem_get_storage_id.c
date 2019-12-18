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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ FDFSStorageIdInfo ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* fdfs_get_storage_id_by_ip (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tracker_mem_get_storage_id(const char *group_name, \
		const char *pIpAddr, char *storage_id)
{
	FDFSStorageIdInfo *pStorageIdInfo;
	pStorageIdInfo = fdfs_get_storage_id_by_ip(group_name, pIpAddr);
	if (pStorageIdInfo == NULL)
	{
		return ENOENT;
	}

	strcpy(storage_id, pStorageIdInfo->id);
	return 0;
}