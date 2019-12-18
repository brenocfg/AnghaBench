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
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  conn_pool_close_connection_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  conn_pool_disconnect_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_connection_pool ; 
 scalar_t__ g_use_connection_pool ; 

void tracker_close_connection_ex(ConnectionInfo *conn, \
	const bool bForceClose)
{
	if (g_use_connection_pool)
	{
		conn_pool_close_connection_ex(&g_connection_pool, \
			conn, bForceClose);
	}
	else
	{
		conn_pool_disconnect_server(conn);
	}
}