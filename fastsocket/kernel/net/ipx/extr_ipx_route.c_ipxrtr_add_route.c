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
struct ipx_route {int ir_routed; int /*<<< orphan*/  ir_router_node; struct ipx_interface* ir_intrfc; int /*<<< orphan*/  ir_net; int /*<<< orphan*/  node; int /*<<< orphan*/  refcnt; } ;
struct ipx_interface {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPX_NODE_LEN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct ipx_interface* ipx_internal_net ; 
 int /*<<< orphan*/  ipx_routes ; 
 int /*<<< orphan*/  ipx_routes_lock ; 
 int /*<<< orphan*/  ipxrtr_hold (struct ipx_route*) ; 
 struct ipx_route* ipxrtr_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipxrtr_put (struct ipx_route*) ; 
 struct ipx_route* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int ipxrtr_add_route(__be32 network, struct ipx_interface *intrfc,
		     unsigned char *node)
{
	struct ipx_route *rt;
	int rc;

	/* Get a route structure; either existing or create */
	rt = ipxrtr_lookup(network);
	if (!rt) {
		rt = kmalloc(sizeof(*rt), GFP_ATOMIC);
		rc = -EAGAIN;
		if (!rt)
			goto out;

		atomic_set(&rt->refcnt, 1);
		ipxrtr_hold(rt);
		write_lock_bh(&ipx_routes_lock);
		list_add(&rt->node, &ipx_routes);
		write_unlock_bh(&ipx_routes_lock);
	} else {
		rc = -EEXIST;
		if (intrfc == ipx_internal_net)
			goto out_put;
	}

	rt->ir_net 	= network;
	rt->ir_intrfc 	= intrfc;
	if (!node) {
		memset(rt->ir_router_node, '\0', IPX_NODE_LEN);
		rt->ir_routed = 0;
	} else {
		memcpy(rt->ir_router_node, node, IPX_NODE_LEN);
		rt->ir_routed = 1;
	}

	rc = 0;
out_put:
	ipxrtr_put(rt);
out:
	return rc;
}