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

/* Variables and functions */
 int /*<<< orphan*/ * sunrpc_table_header ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_unregister_transport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xs_bc_tcp_transport ; 
 int /*<<< orphan*/  xs_local_transport ; 
 int /*<<< orphan*/  xs_tcp_transport ; 
 int /*<<< orphan*/  xs_udp_transport ; 

void cleanup_socket_xprt(void)
{
#ifdef RPC_DEBUG
	if (sunrpc_table_header) {
		unregister_sysctl_table(sunrpc_table_header);
		sunrpc_table_header = NULL;
	}
#endif

	xprt_unregister_transport(&xs_local_transport);
	xprt_unregister_transport(&xs_udp_transport);
	xprt_unregister_transport(&xs_tcp_transport);
	xprt_unregister_transport(&xs_bc_tcp_transport);
}