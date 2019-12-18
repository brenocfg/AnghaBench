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
typedef  int /*<<< orphan*/  TrackerServerInfo ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int TRACKER_SYS_FILE_COUNT ; 
 int /*<<< orphan*/  fdfs_server_sock_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tracker_connect_server (int /*<<< orphan*/ *,int*) ; 
 int tracker_get_sys_files_end (int /*<<< orphan*/ *) ; 
 int tracker_get_sys_files_start (int /*<<< orphan*/ *) ; 
 int tracker_mem_get_one_sys_file (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tracker_mem_get_sys_files(TrackerServerInfo *pTrackerServer)
{
	ConnectionInfo *conn;
	int result;
	int index;

    fdfs_server_sock_reset(pTrackerServer);
	if ((conn=tracker_connect_server(pTrackerServer, &result)) == NULL)
	{
		return result;
	}

	if ((result=tracker_get_sys_files_start(conn)) != 0)
	{
		tracker_close_connection_ex(conn, true);
		return result;
	}

	for (index=0; index<TRACKER_SYS_FILE_COUNT; index++)
	{
		result = tracker_mem_get_one_sys_file(conn, index);
		if (result != 0)
		{
			break;
		}
	}

	result = tracker_get_sys_files_end(conn);
	tracker_close_connection_ex(conn, result != 0);

	return result;
}