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
typedef  int /*<<< orphan*/  FDFSMetaData ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FDFS_UPLOAD_BY_BUFF ; 
 int /*<<< orphan*/  STORAGE_PROTO_CMD_UPLOAD_SLAVE_FILE ; 
 int storage_do_upload_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const,char const*,char const*,char const*,int /*<<< orphan*/  const*,int const,char*,char*) ; 

int storage_upload_slave_by_filebuff(ConnectionInfo *pTrackerServer, \
		ConnectionInfo *pStorageServer, const char *file_buff, \
		const int64_t file_size, const char *master_filename, \
		const char *prefix_name, const char *file_ext_name, \
		const FDFSMetaData *meta_list, const int meta_count, \
		char *group_name, char *remote_filename)
{
	if (master_filename == NULL || *master_filename == '\0' || \
		prefix_name == NULL || *prefix_name == '\0' || \
		group_name == NULL || *group_name == '\0')
	{
		return EINVAL;
	}

	return storage_do_upload_file(pTrackerServer, pStorageServer, \
			0, STORAGE_PROTO_CMD_UPLOAD_SLAVE_FILE, \
			FDFS_UPLOAD_BY_BUFF, file_buff, NULL, \
			file_size, master_filename, prefix_name, \
			file_ext_name, meta_list, meta_count, \
			group_name, remote_filename);
}