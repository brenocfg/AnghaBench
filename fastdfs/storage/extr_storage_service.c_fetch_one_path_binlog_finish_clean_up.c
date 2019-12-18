#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fast_task_info {scalar_t__ arg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * extra_arg; } ;
typedef  TYPE_1__ StorageClientInfo ;
typedef  int /*<<< orphan*/  StorageBinLogReader ;

/* Variables and functions */
 int MAX_PATH_SIZE ; 
 scalar_t__ fileExists (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mark_filename_by_reader (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  storage_reader_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  storage_reader_remove_from_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void fetch_one_path_binlog_finish_clean_up(struct fast_task_info *pTask)
{
	StorageClientInfo *pClientInfo;
	StorageBinLogReader *pReader;
	char full_filename[MAX_PATH_SIZE];

	pClientInfo = (StorageClientInfo *)pTask->arg;
	pReader = (StorageBinLogReader *)pClientInfo->extra_arg;
	if (pReader == NULL)
	{
		return;
	}

	pClientInfo->extra_arg = NULL;

    storage_reader_remove_from_list(pReader);
	storage_reader_destroy(pReader);
	get_mark_filename_by_reader(pReader, full_filename);
	if (fileExists(full_filename))
	{
		unlink(full_filename);
	}

	free(pReader);
}