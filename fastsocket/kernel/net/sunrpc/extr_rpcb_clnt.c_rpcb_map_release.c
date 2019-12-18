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
struct rpcbind_args {struct rpcbind_args* r_addr; int /*<<< orphan*/  r_xprt; int /*<<< orphan*/  r_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpcbind_args*) ; 
 int /*<<< orphan*/  rpcb_wake_rpcbind_waiters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpcb_map_release(void *data)
{
	struct rpcbind_args *map = data;

	rpcb_wake_rpcbind_waiters(map->r_xprt, map->r_status);
	xprt_put(map->r_xprt);
	kfree(map->r_addr);
	kfree(map);
}