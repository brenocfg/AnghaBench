#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int count; TYPE_2__** all_servers; } ;
struct TYPE_5__ {scalar_t__ success_delete_count; scalar_t__ success_upload_count; } ;
struct TYPE_6__ {TYPE_1__ stat; } ;
typedef  TYPE_2__ FDFSStorageDetail ;
typedef  TYPE_3__ FDFSGroupInfo ;

/* Variables and functions */

int tracker_get_group_file_count(FDFSGroupInfo *pGroup)
{
	int count;
	FDFSStorageDetail **ppServer;
	FDFSStorageDetail **ppServerEnd;

	count = 0;
	ppServerEnd = pGroup->all_servers + pGroup->count;
	for (ppServer=pGroup->all_servers; ppServer<ppServerEnd; ppServer++)
	{
		count += (*ppServer)->stat.success_upload_count - \
				(*ppServer)->stat.success_delete_count;
	}

	return count;
}