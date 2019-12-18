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
struct rpc_xprt {int /*<<< orphan*/ * address_strings; } ;

/* Variables and functions */
 size_t RPC_DISPLAY_HEX_PORT ; 
 size_t RPC_DISPLAY_PORT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_format_common_peer_ports (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_update_peer_port(struct rpc_xprt *xprt)
{
	kfree(xprt->address_strings[RPC_DISPLAY_HEX_PORT]);
	kfree(xprt->address_strings[RPC_DISPLAY_PORT]);

	xs_format_common_peer_ports(xprt);
}