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
struct sockaddr {int dummy; } ;
struct rpc_xprt {size_t addrlen; int /*<<< orphan*/  addr; } ;
struct rpc_clnt {struct rpc_xprt* cl_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ *,size_t) ; 

size_t rpc_peeraddr(struct rpc_clnt *clnt, struct sockaddr *buf, size_t bufsize)
{
	size_t bytes;
	struct rpc_xprt *xprt = clnt->cl_xprt;

	bytes = sizeof(xprt->addr);
	if (bytes > bufsize)
		bytes = bufsize;
	memcpy(buf, &clnt->cl_xprt->addr, bytes);
	return xprt->addrlen;
}