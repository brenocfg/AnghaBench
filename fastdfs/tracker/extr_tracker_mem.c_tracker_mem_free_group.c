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
struct TYPE_3__ {int /*<<< orphan*/ * last_sync_timestamps; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/ * http_servers; int /*<<< orphan*/ * all_servers; int /*<<< orphan*/ * active_servers; int /*<<< orphan*/ * sorted_servers; } ;
typedef  TYPE_1__ FDFSGroupInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ g_http_check_interval ; 
 int /*<<< orphan*/  tracker_free_last_sync_timestamps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracker_mem_free_storages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tracker_mem_free_group(FDFSGroupInfo *pGroup)
{
	if (pGroup->sorted_servers != NULL)
	{
		free(pGroup->sorted_servers);
		pGroup->sorted_servers = NULL;
	}

	if (pGroup->active_servers != NULL)
	{
		free(pGroup->active_servers);
		pGroup->active_servers = NULL;
	}

	if (pGroup->all_servers != NULL)
	{
		tracker_mem_free_storages(pGroup->all_servers, \
				pGroup->alloc_size);
		pGroup->all_servers = NULL;
	}

#ifdef WITH_HTTPD
	if (g_http_check_interval > 0)
	{
		if (pGroup->http_servers != NULL)
		{
			free(pGroup->http_servers);
			pGroup->http_servers = NULL;
		}
	}
#endif

	tracker_free_last_sync_timestamps(pGroup->last_sync_timestamps, \
				pGroup->alloc_size);
	pGroup->last_sync_timestamps = NULL;
}