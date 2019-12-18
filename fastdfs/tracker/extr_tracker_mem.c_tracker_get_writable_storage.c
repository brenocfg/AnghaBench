#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ store_server; } ;
struct TYPE_4__ {int current_write_server; int active_count; int /*<<< orphan*/ * pStoreServer; int /*<<< orphan*/ ** active_servers; } ;
typedef  int /*<<< orphan*/  FDFSStorageDetail ;
typedef  TYPE_1__ FDFSGroupInfo ;

/* Variables and functions */
 scalar_t__ FDFS_STORE_SERVER_ROUND_ROBIN ; 
 TYPE_3__ g_groups ; 

FDFSStorageDetail *tracker_get_writable_storage(FDFSGroupInfo *pStoreGroup)
{
	int write_server_index;
	if (g_groups.store_server == FDFS_STORE_SERVER_ROUND_ROBIN)
	{
		write_server_index = pStoreGroup->current_write_server++;
		if (pStoreGroup->current_write_server >= \
				pStoreGroup->active_count)
		{
			pStoreGroup->current_write_server = 0;
		}

		if (write_server_index >= pStoreGroup->active_count)
		{
			write_server_index = 0;
		}
		return  *(pStoreGroup->active_servers + write_server_index);
	}
	else //use the first server
	{
		return pStoreGroup->pStoreServer;
	}
}