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
struct TYPE_2__ {char** paths; } ;
typedef  int /*<<< orphan*/  StorageBinLogReader ;

/* Variables and functions */
 TYPE_1__ g_fdfs_store_paths ; 
 int recovery_reader_init (char*,int /*<<< orphan*/ *) ; 
 int storage_do_split_trunk_binlog (int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  storage_reader_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int storage_disk_recovery_split_trunk_binlog(const int store_path_index)
{
	char *pBasePath;
	StorageBinLogReader reader;
	int result;

	pBasePath = g_fdfs_store_paths.paths[store_path_index];
	if ((result=recovery_reader_init(pBasePath, &reader)) != 0)
	{
		storage_reader_destroy(&reader);
		return result;
	}

	result = storage_do_split_trunk_binlog(store_path_index, &reader);

	storage_reader_destroy(&reader);
	return result;
}