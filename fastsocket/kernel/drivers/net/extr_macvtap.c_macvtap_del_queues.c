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
struct net_device {int dummy; } ;
struct macvtap_queue {int /*<<< orphan*/  sk; int /*<<< orphan*/  vlan; } ;
struct macvlan_dev {int /*<<< orphan*/  tap; } ;

/* Variables and functions */
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct macvtap_queue* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void macvtap_del_queues(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct macvtap_queue *q;

	q = rtnl_dereference(vlan->tap);
	if (!q)
		return;

	rcu_assign_pointer(vlan->tap, NULL);
	rcu_assign_pointer(q->vlan, NULL);

	synchronize_rcu();
	sock_put(&q->sk);
}