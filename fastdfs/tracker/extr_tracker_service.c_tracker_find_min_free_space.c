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
struct TYPE_5__ {scalar_t__ active_count; scalar_t__ free_mb; int /*<<< orphan*/  total_mb; TYPE_1__** active_servers; } ;
struct TYPE_4__ {scalar_t__ free_mb; int /*<<< orphan*/  total_mb; } ;
typedef  TYPE_1__ FDFSStorageDetail ;
typedef  TYPE_2__ FDFSGroupInfo ;

/* Variables and functions */

__attribute__((used)) static void tracker_find_min_free_space(FDFSGroupInfo *pGroup)
{
	FDFSStorageDetail **ppServerEnd;
	FDFSStorageDetail **ppServer;

	if (pGroup->active_count == 0)
	{
		return;
	}

	pGroup->total_mb = (*(pGroup->active_servers))->total_mb;
	pGroup->free_mb = (*(pGroup->active_servers))->free_mb;
	ppServerEnd = pGroup->active_servers + pGroup->active_count;
	for (ppServer=pGroup->active_servers+1; \
		ppServer<ppServerEnd; ppServer++)
	{
		if ((*ppServer)->free_mb < pGroup->free_mb)
		{
			pGroup->total_mb = (*ppServer)->total_mb;
			pGroup->free_mb = (*ppServer)->free_mb;
		}
	}
}