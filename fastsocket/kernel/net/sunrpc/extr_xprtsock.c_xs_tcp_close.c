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
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xs_close (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xs_tcp_shutdown (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_tcp_close(struct rpc_xprt *xprt)
{
	if (test_and_clear_bit(XPRT_CONNECTION_CLOSE, &xprt->state))
		xs_close(xprt);
	else
		xs_tcp_shutdown(xprt);
}