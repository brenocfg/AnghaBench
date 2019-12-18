#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FDFS_DOWNLOAD_TO_FILE ; 
 int storage_do_download_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int storage_download_file_to_file(ConnectionInfo *pTrackerServer, \
			ConnectionInfo *pStorageServer, \
			const char *group_name, const char *remote_filename, \
			const char *local_filename, int64_t *file_size)
{
	char *pLocalFilename;
	pLocalFilename = (char *)local_filename;
	return storage_do_download_file(pTrackerServer, pStorageServer, \
			FDFS_DOWNLOAD_TO_FILE, group_name, remote_filename, \
			&pLocalFilename, NULL, file_size);
}