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
typedef  scalar_t__ DownloadCallback ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FDFS_DOWNLOAD_TO_CALLBACK ; 
 int storage_do_download_file_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,char**,void*,int /*<<< orphan*/ *) ; 

int storage_download_file_ex(ConnectionInfo *pTrackerServer, \
		ConnectionInfo *pStorageServer, \
		const char *group_name, const char *remote_filename, \
		const int64_t file_offset, const int64_t download_bytes, \
		DownloadCallback callback, void *arg, int64_t *file_size)
{
	char *pCallback;
	pCallback = (char *)callback;
	return storage_do_download_file_ex(pTrackerServer, pStorageServer, \
		FDFS_DOWNLOAD_TO_CALLBACK, group_name, remote_filename, \
		file_offset, download_bytes, &pCallback, arg, file_size);
}