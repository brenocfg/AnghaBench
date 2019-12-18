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
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  FDFS_UPLOAD_BY_FILE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int storage_do_append_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 

int storage_append_by_filename(ConnectionInfo *pTrackerServer, \
		ConnectionInfo *pStorageServer, const char *local_filename,\
		const char *group_name, const char *appender_filename)
{
	struct stat stat_buf;

	if (appender_filename == NULL || *appender_filename == '\0' \
	 || group_name == NULL || *group_name == '\0')
	{
		return EINVAL;
	}

	if (stat(local_filename, &stat_buf) != 0)
	{
		return errno != 0 ? errno : EPERM;
	}

	if (!S_ISREG(stat_buf.st_mode))
	{
		return EINVAL;
	}
	return storage_do_append_file(pTrackerServer, pStorageServer, \
		FDFS_UPLOAD_BY_FILE, local_filename, \
		NULL, stat_buf.st_size, group_name, appender_filename);
}