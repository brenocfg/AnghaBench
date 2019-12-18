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
struct ipx_route_definition {int /*<<< orphan*/  ipx_router_node; int /*<<< orphan*/  ipx_network; int /*<<< orphan*/  ipx_router_network; } ;
struct ipx_interface {int dummy; } ;

/* Variables and functions */
 int ENETUNREACH ; 
 struct ipx_interface* ipxitf_find_using_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipxitf_put (struct ipx_interface*) ; 
 int ipxrtr_add_route (int /*<<< orphan*/ ,struct ipx_interface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipxrtr_create(struct ipx_route_definition *rd)
{
	struct ipx_interface *intrfc;
	int rc = -ENETUNREACH;

	/* Find the appropriate interface */
	intrfc = ipxitf_find_using_net(rd->ipx_router_network);
	if (!intrfc)
		goto out;
	rc = ipxrtr_add_route(rd->ipx_network, intrfc, rd->ipx_router_node);
	ipxitf_put(intrfc);
out:
	return rc;
}