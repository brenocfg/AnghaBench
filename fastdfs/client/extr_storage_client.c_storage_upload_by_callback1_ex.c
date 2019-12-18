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
typedef  int /*<<< orphan*/  new_group_name ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ UploadCallback ;
typedef  int /*<<< orphan*/  FDFSMetaData ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 char* FDFS_FILE_ID_SEPERATOR ; 
 int /*<<< orphan*/  FDFS_GROUP_NAME_MAX_LEN ; 
 int /*<<< orphan*/  FDFS_UPLOAD_BY_CALLBACK ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 
 int storage_do_upload_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,char const,int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int const,char*,char*) ; 

int storage_upload_by_callback1_ex(ConnectionInfo *pTrackerServer, \
		ConnectionInfo *pStorageServer, const int store_path_index, \
		const char cmd, UploadCallback callback, void *arg, \
		const int64_t file_size, const char *file_ext_name, \
		const FDFSMetaData *meta_list, const int meta_count, \
		const char *group_name, char *file_id)
{
	char new_group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	char remote_filename[128];
	int result;

	if (group_name == NULL)
	{
		*new_group_name = '\0';
	}
	else
	{
		snprintf(new_group_name, sizeof(new_group_name), \
				"%s", group_name);
	}

	result = storage_do_upload_file(pTrackerServer, \
			pStorageServer, store_path_index, \
			cmd, FDFS_UPLOAD_BY_CALLBACK, (char *)callback, arg, \
			file_size, NULL, NULL, file_ext_name, \
			meta_list, meta_count, \
			new_group_name, remote_filename);
	if (result == 0)
	{
		sprintf(file_id, "%s%c%s", new_group_name, \
			FDFS_FILE_ID_SEPERATOR, remote_filename);
	}
	else
	{
		file_id[0] = '\0';
	}

	return result;
}