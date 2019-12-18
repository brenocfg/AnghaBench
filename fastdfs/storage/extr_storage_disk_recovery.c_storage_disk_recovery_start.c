#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char** paths; } ;
struct TYPE_5__ {TYPE_1__* ips; } ;
struct TYPE_4__ {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int EINTR ; 
 int ENOENT ; 
 int /*<<< orphan*/  FDFS_STORAGE_STATUS_RECOVERY ; 
 int MAX_PATH_SIZE ; 
 scalar_t__ g_continue_flag ; 
 TYPE_3__ g_fdfs_store_paths ; 
 int /*<<< orphan*/  g_my_server_id_str ; 
 TYPE_2__ g_tracker_client_ip ; 
 int /*<<< orphan*/  recovery_get_mark_filename (char*,char*) ; 
 int recovery_get_src_storage_server (int /*<<< orphan*/ *) ; 
 int recovery_init_binlog_file (char*) ; 
 int recovery_init_mark_file (char*,int) ; 
 int storage_disk_recovery_finish (char*) ; 
 int storage_disk_recovery_split_trunk_binlog (int const) ; 
 int storage_do_fetch_binlog (int /*<<< orphan*/ *,int const) ; 
 scalar_t__ storage_report_storage_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tracker_make_connection (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int storage_disk_recovery_start(const int store_path_index)
{
	ConnectionInfo srcStorage;
	ConnectionInfo *pStorageConn;
	int result;
	char *pBasePath;

	pBasePath = g_fdfs_store_paths.paths[store_path_index];
	if ((result=recovery_init_mark_file(pBasePath, false)) != 0)
	{
		return result;
	}

	if ((result=recovery_init_binlog_file(pBasePath)) != 0)
	{
		return result;
	}

	if ((result=recovery_get_src_storage_server(&srcStorage)) != 0)
	{
		if (result == ENOENT)
		{
			return storage_disk_recovery_finish(pBasePath);
		}
		else
		{
			return result;
		}
	}

	while (g_continue_flag)
	{
		if (storage_report_storage_status(g_my_server_id_str, \
			g_tracker_client_ip.ips[0].address,
            FDFS_STORAGE_STATUS_RECOVERY) == 0)
		{
			break;
		}
	}

	if (!g_continue_flag)
	{
		return EINTR;
	}

	if ((pStorageConn=tracker_make_connection(&srcStorage, &result)) == NULL)
	{
		return result;
	}

	result = storage_do_fetch_binlog(pStorageConn, store_path_index);
	tracker_close_connection_ex(pStorageConn, true);
	if (result != 0)
	{
		return result;
	}

	//set fetch binlog done
	if ((result=recovery_init_mark_file(pBasePath, true)) != 0)
	{
		return result;
	}

	if ((result=storage_disk_recovery_split_trunk_binlog( \
			store_path_index)) != 0)
	{
		char markFullFilename[MAX_PATH_SIZE];
		unlink(recovery_get_mark_filename(pBasePath, markFullFilename));
		return result;
	}

	return 0;
}