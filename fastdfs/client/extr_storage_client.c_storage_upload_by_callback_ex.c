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
typedef  scalar_t__ UploadCallback ;
typedef  int /*<<< orphan*/  FDFSMetaData ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FDFS_UPLOAD_BY_CALLBACK ; 
 int storage_do_upload_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,char const,int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int const,char*,char*) ; 

int storage_upload_by_callback_ex(ConnectionInfo *pTrackerServer, \
		ConnectionInfo *pStorageServer, const int store_path_index, \
		const char cmd, UploadCallback callback, void *arg, \
		const int64_t file_size, const char *file_ext_name, \
		const FDFSMetaData *meta_list, const int meta_count, \
		char *group_name, char *remote_filename)
{
	return storage_do_upload_file(pTrackerServer, pStorageServer, \
		store_path_index, cmd, FDFS_UPLOAD_BY_CALLBACK, \
		(char *)callback, arg, file_size, NULL, NULL, \
		file_ext_name, meta_list, meta_count, \
		group_name, remote_filename);
}