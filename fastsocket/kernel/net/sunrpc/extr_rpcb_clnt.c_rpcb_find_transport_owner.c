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
struct rpc_clnt {scalar_t__ cl_xprt; struct rpc_clnt* cl_parent; scalar_t__ cl_autobind; } ;

/* Variables and functions */

__attribute__((used)) static struct rpc_clnt *rpcb_find_transport_owner(struct rpc_clnt *clnt)
{
	struct rpc_clnt *parent = clnt->cl_parent;

	while (parent != clnt) {
		if (parent->cl_xprt != clnt->cl_xprt)
			break;
		if (clnt->cl_autobind)
			break;
		clnt = parent;
		parent = parent->cl_parent;
	}
	return clnt;
}