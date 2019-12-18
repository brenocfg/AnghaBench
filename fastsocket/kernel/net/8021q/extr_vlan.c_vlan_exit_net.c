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
struct vlan_net {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vlan_net*) ; 
 struct vlan_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_kill_links (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_link_ops ; 
 int /*<<< orphan*/  vlan_net_id ; 
 int /*<<< orphan*/  vlan_proc_cleanup (struct net*) ; 

__attribute__((used)) static void vlan_exit_net(struct net *net)
{
	struct vlan_net *vn;

	vn = net_generic(net, vlan_net_id);
	rtnl_kill_links(net, &vlan_link_ops);
	vlan_proc_cleanup(net);
	kfree(vn);
}