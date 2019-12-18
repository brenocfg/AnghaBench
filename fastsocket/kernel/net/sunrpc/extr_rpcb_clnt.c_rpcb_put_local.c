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
struct rpc_clnt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpcb_clnt_lock ; 
 struct rpc_clnt* rpcb_local_clnt ; 
 struct rpc_clnt* rpcb_local_clnt4 ; 
 scalar_t__ rpcb_users ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rpcb_put_local(void)
{
	struct rpc_clnt *clnt = rpcb_local_clnt;
	struct rpc_clnt *clnt4 = rpcb_local_clnt4;
	int shutdown;

	spin_lock(&rpcb_clnt_lock);
	if (--rpcb_users == 0) {
		rpcb_local_clnt = NULL;
		rpcb_local_clnt4 = NULL;
	}
	shutdown = !rpcb_users;
	spin_unlock(&rpcb_clnt_lock);

	if (shutdown) {
		/*
		 * cleanup_rpcb_clnt - remove xprtsock's sysctls, unregister
		 */
		if (clnt4)
			rpc_shutdown_client(clnt4);
		if (clnt)
			rpc_shutdown_client(clnt);
	}
}