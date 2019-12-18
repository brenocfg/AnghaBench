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
struct rpc_xprt {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_CONNECTION_CLOSE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_force_disconnect (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_tcp_force_close(struct rpc_xprt *xprt)
{
	set_bit(XPRT_CONNECTION_CLOSE, &xprt->state);
	xprt_force_disconnect(xprt);
}