#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int port; int sock; int /*<<< orphan*/  ip_addr; } ;
typedef  TYPE_1__ ConnectionInfo ;

/* Variables and functions */
 int fdfs_deal_no_body_cmd (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tracker_close_connection_ex (TYPE_1__*,int) ; 
 TYPE_1__* tracker_make_connection (TYPE_1__*,int*) ; 

int fdfs_deal_no_body_cmd_ex(const char *ip_addr, const int port, const int cmd)
{
	ConnectionInfo *conn;
	ConnectionInfo server_info;
	int result;

	strcpy(server_info.ip_addr, ip_addr);
	server_info.port = port;
	server_info.sock = -1;
	if ((conn=tracker_make_connection(&server_info, &result)) == NULL)
	{
		return result;
	}

	result = fdfs_deal_no_body_cmd(conn, cmd);
	tracker_close_connection_ex(conn, result != 0);
	return result;
}