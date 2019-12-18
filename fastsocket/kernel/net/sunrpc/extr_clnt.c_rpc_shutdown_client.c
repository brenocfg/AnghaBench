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
struct rpc_clnt {int /*<<< orphan*/  cl_tasks; int /*<<< orphan*/  cl_server; int /*<<< orphan*/  cl_protname; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  destroy_wait ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_killall_tasks (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_release_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rpc_shutdown_client(struct rpc_clnt *clnt)
{
	dprintk("RPC:       shutting down %s client for %s\n",
			clnt->cl_protname, clnt->cl_server);

	while (!list_empty(&clnt->cl_tasks)) {
		rpc_killall_tasks(clnt);
		wait_event_timeout(destroy_wait,
			list_empty(&clnt->cl_tasks), 1*HZ);
	}

	rpc_release_client(clnt);
}