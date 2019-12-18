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
struct rpc_xprt {int /*<<< orphan*/  xprt_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpc_xprt*) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_free_all_slots (struct rpc_xprt*) ; 

void xprt_free(struct rpc_xprt *xprt)
{
	put_net(xprt->xprt_net);
	xprt_free_all_slots(xprt);
	kfree(xprt);
}