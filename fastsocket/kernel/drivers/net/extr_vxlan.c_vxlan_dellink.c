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
struct vxlan_net {int /*<<< orphan*/  sock_lock; } ;
struct vxlan_dev {int /*<<< orphan*/  next; int /*<<< orphan*/  hlist; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct vxlan_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  vxlan_net_id ; 

__attribute__((used)) static void vxlan_dellink(struct net_device *dev)
{
	struct vxlan_net *vn = net_generic(dev_net(dev), vxlan_net_id);
	struct vxlan_dev *vxlan = netdev_priv(dev);

	spin_lock(&vn->sock_lock);
	if (!hlist_unhashed(&vxlan->hlist))
		hlist_del_rcu(&vxlan->hlist);
	spin_unlock(&vn->sock_lock);

	list_del(&vxlan->next);
	unregister_netdevice(dev);
}