#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpcbind_args {scalar_t__ r_port; int r_status; struct rpc_xprt* r_xprt; } ;
struct rpc_xprt {TYPE_1__* ops; int /*<<< orphan*/  bind_index; } ;
struct rpc_task {int tk_status; int /*<<< orphan*/  tk_pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_port ) (struct rpc_xprt*,scalar_t__) ;} ;

/* Variables and functions */
 int EACCES ; 
 int EIO ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct rpc_xprt*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct rpc_xprt*,scalar_t__) ; 
 int /*<<< orphan*/  xprt_set_bound (struct rpc_xprt*) ; 

__attribute__((used)) static void rpcb_getport_done(struct rpc_task *child, void *data)
{
	struct rpcbind_args *map = data;
	struct rpc_xprt *xprt = map->r_xprt;
	int status = child->tk_status;

	/* Garbage reply: retry with a lesser rpcbind version */
	if (status == -EIO)
		status = -EPROTONOSUPPORT;

	/* rpcbind server doesn't support this rpcbind protocol version */
	if (status == -EPROTONOSUPPORT)
		xprt->bind_index++;

	if (status < 0) {
		/* rpcbind server not available on remote host? */
		xprt->ops->set_port(xprt, 0);
	} else if (map->r_port == 0) {
		/* Requested RPC service wasn't registered on remote host */
		xprt->ops->set_port(xprt, 0);
		status = -EACCES;
	} else {
		/* Succeeded */
		xprt->ops->set_port(xprt, map->r_port);
		xprt_set_bound(xprt);
		status = 0;
	}

	dprintk("RPC: %5u rpcb_getport_done(status %d, port %u)\n",
			child->tk_pid, status, map->r_port);

	map->r_status = status;
}