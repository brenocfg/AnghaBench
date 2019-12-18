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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FDFSMetaData ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FDFS_UPLOAD_BY_FILE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int errno ; 
 char* fdfs_get_file_ext_name (char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int storage_do_upload_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,char const,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int const,char*,char*) ; 

int storage_upload_by_filename_ex(ConnectionInfo *pTrackerServer, \
		ConnectionInfo *pStorageServer, const int store_path_index, \
		const char cmd, const char *local_filename, \
		const char *file_ext_name, const FDFSMetaData *meta_list, \
		const int meta_count, char *group_name, char *remote_filename)
{
	struct stat stat_buf;

	if (stat(local_filename, &stat_buf) != 0)
	{
		group_name[0] = '\0';
		remote_filename[0] = '\0';
		return errno;
	}

	if (!S_ISREG(stat_buf.st_mode))
	{
		group_name[0] = '\0';
		remote_filename[0] = '\0';
		return EINVAL;
	}

	if (file_ext_name == NULL)
	{
		file_ext_name = fdfs_get_file_ext_name(local_filename);
	}

	return storage_do_upload_file(pTrackerServer, pStorageServer, \
			store_path_index, cmd, \
			FDFS_UPLOAD_BY_FILE, local_filename, \
			NULL, stat_buf.st_size, NULL, NULL, file_ext_name, \
			meta_list, meta_count, group_name, remote_filename);
}