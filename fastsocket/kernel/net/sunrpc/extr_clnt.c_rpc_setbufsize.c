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
struct rpc_xprt {TYPE_1__* ops; } ;
struct rpc_clnt {struct rpc_xprt* cl_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_buffer_size ) (struct rpc_xprt*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,unsigned int,unsigned int) ; 

void
rpc_setbufsize(struct rpc_clnt *clnt, unsigned int sndsize, unsigned int rcvsize)
{
	struct rpc_xprt *xprt = clnt->cl_xprt;
	if (xprt->ops->set_buffer_size)
		xprt->ops->set_buffer_size(xprt, sndsize, rcvsize);
}