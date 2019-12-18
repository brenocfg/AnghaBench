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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int store_path_count; int /*<<< orphan*/  stat; scalar_t__ current_write_path; scalar_t__ upload_priority; scalar_t__ subdir_count_per_path; scalar_t__ changelog_offset; scalar_t__ free_mb; scalar_t__ total_mb; scalar_t__ sync_until_timestamp; int /*<<< orphan*/ * psync_src_server; int /*<<< orphan*/ * path_free_mbs; int /*<<< orphan*/ * path_total_mbs; } ;
typedef  int /*<<< orphan*/  FDFSStorageStat ;
typedef  TYPE_1__ FDFSStorageDetail ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tracker_mem_clear_storage_fields(FDFSStorageDetail *pStorageServer)
{
        if (pStorageServer->path_total_mbs != NULL)
	{
		memset(pStorageServer->path_total_mbs, 0, sizeof(int64_t) \
			* pStorageServer->store_path_count);
	}

        if (pStorageServer->path_free_mbs != NULL)
	{
		memset(pStorageServer->path_free_mbs, 0, sizeof(int64_t) \
			* pStorageServer->store_path_count);
	}

	pStorageServer->psync_src_server = NULL;
	pStorageServer->sync_until_timestamp = 0;
	pStorageServer->total_mb = 0;
	pStorageServer->free_mb = 0;
	pStorageServer->changelog_offset = 0;
	pStorageServer->store_path_count = 0;
	pStorageServer->subdir_count_per_path = 0;
	pStorageServer->upload_priority = 0;
	pStorageServer->current_write_path = 0;

	memset(&(pStorageServer->stat), 0, sizeof(FDFSStorageStat));
}