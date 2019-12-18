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
struct rpc_xprt {unsigned int max_reqs; unsigned int min_reqs; int /*<<< orphan*/  num_reqs; int /*<<< orphan*/  free; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_list; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned int) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_free (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_init (struct rpc_xprt*,struct net*) ; 

struct rpc_xprt *xprt_alloc(struct net *net, size_t size,
		unsigned int num_prealloc,
		unsigned int max_alloc)
{
	struct rpc_xprt *xprt;
	struct rpc_rqst *req;
	int i;

	xprt = kzalloc(size, GFP_KERNEL);
	if (xprt == NULL)
		goto out;

	xprt_init(xprt, net);

	for (i = 0; i < num_prealloc; i++) {
		req = kzalloc(sizeof(struct rpc_rqst), GFP_KERNEL);
		if (!req)
			break;
		list_add(&req->rq_list, &xprt->free);
	}
	if (i < num_prealloc)
		goto out_free;
	if (max_alloc > num_prealloc)
		xprt->max_reqs = max_alloc;
	else
		xprt->max_reqs = num_prealloc;
	xprt->min_reqs = num_prealloc;
	atomic_set(&xprt->num_reqs, num_prealloc);

	return xprt;

out_free:
	xprt_free(xprt);
out:
	return NULL;
}