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
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xprt_disconnect_done (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xs_sock_reset_connection_flags (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_sock_mark_closed(struct rpc_xprt *xprt)
{
	xs_sock_reset_connection_flags(xprt);
	/* Mark transport as closed and wake up all pending tasks */
	xprt_disconnect_done(xprt);
}