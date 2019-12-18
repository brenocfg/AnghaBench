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
struct sockaddr {int dummy; } ;
struct rpc_xprt {void** address_strings; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t RPC_DISPLAY_HEX_PORT ; 
 size_t RPC_DISPLAY_PORT ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int rpc_get_port (struct sockaddr*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 struct sockaddr* xs_addr (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_format_common_peer_ports(struct rpc_xprt *xprt)
{
	struct sockaddr *sap = xs_addr(xprt);
	char buf[128];

	(void)snprintf(buf, sizeof(buf), "%u", rpc_get_port(sap));
	xprt->address_strings[RPC_DISPLAY_PORT] = kstrdup(buf, GFP_KERNEL);

	(void)snprintf(buf, sizeof(buf), "%4hx", rpc_get_port(sap));
	xprt->address_strings[RPC_DISPLAY_HEX_PORT] = kstrdup(buf, GFP_KERNEL);
}