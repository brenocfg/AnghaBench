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
struct ipx_interface_definition {int /*<<< orphan*/  ipx_node; int /*<<< orphan*/  ipx_network; } ;
struct ipx_interface {int /*<<< orphan*/  if_node; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EAGAIN ; 
 int EEXIST ; 
 int /*<<< orphan*/  IPX_NODE_LEN ; 
 struct ipx_interface* ipx_internal_net ; 
 struct ipx_interface* ipx_primary_net ; 
 int ipxitf_add_local_route (struct ipx_interface*) ; 
 struct ipx_interface* ipxitf_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct ipx_interface* ipxitf_find_using_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipxitf_hold (struct ipx_interface*) ; 
 int /*<<< orphan*/  ipxitf_insert (struct ipx_interface*) ; 
 int /*<<< orphan*/  ipxitf_put (struct ipx_interface*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipxitf_create_internal(struct ipx_interface_definition *idef)
{
	struct ipx_interface *intrfc;
	int rc = -EEXIST;

	/* Only one primary network allowed */
	if (ipx_primary_net)
		goto out;

	/* Must have a valid network number */
	rc = -EADDRNOTAVAIL;
	if (!idef->ipx_network)
		goto out;
	intrfc = ipxitf_find_using_net(idef->ipx_network);
	rc = -EADDRINUSE;
	if (intrfc) {
		ipxitf_put(intrfc);
		goto out;
	}
	intrfc = ipxitf_alloc(NULL, idef->ipx_network, 0, NULL, 1, 0);
	rc = -EAGAIN;
	if (!intrfc)
		goto out;
	memcpy((char *)&(intrfc->if_node), idef->ipx_node, IPX_NODE_LEN);
	ipx_internal_net = ipx_primary_net = intrfc;
	ipxitf_hold(intrfc);
	ipxitf_insert(intrfc);

	rc = ipxitf_add_local_route(intrfc);
	ipxitf_put(intrfc);
out:
	return rc;
}