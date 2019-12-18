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
 int EINVAL ; 
 int /*<<< orphan*/  FDFS_UPLOAD_BY_BUFF ; 
 int storage_do_append_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const,char const*,char const*) ; 

int storage_append_by_filebuff(ConnectionInfo *pTrackerServer, \
		ConnectionInfo *pStorageServer, const char *file_buff, \
		const int64_t file_size, const char *group_name, \
		const char *appender_filename)
{
	if (appender_filename == NULL || *appender_filename == '\0' \
	 || group_name == NULL || *group_name == '\0')
	{
		return EINVAL;
	}

	return storage_do_append_file(pTrackerServer, pStorageServer, \
			FDFS_UPLOAD_BY_BUFF, file_buff, NULL, \
			file_size, group_name, appender_filename);
}