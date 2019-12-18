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
 int _notify_reselect_tleader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdfs_server_sock_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tracker_connect_server (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int notify_reselect_tracker_leader(TrackerServerInfo *pTrackerServer)
{
    int result;
    ConnectionInfo *conn;

    fdfs_server_sock_reset(pTrackerServer);
	if ((conn=tracker_connect_server(pTrackerServer, &result)) == NULL)
	{
		return result;
	}

    result = _notify_reselect_tleader(conn);
	tracker_close_connection_ex(conn, result != 0);
    return result;
}