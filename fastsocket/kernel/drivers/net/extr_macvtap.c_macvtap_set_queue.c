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
struct macvtap_queue {struct file* file; int /*<<< orphan*/  sk; int /*<<< orphan*/  tap; int /*<<< orphan*/  vlan; } ;
struct macvlan_dev {struct file* file; int /*<<< orphan*/  sk; int /*<<< orphan*/  tap; int /*<<< orphan*/  vlan; } ;
struct file {struct macvtap_queue* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 struct macvtap_queue* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct macvtap_queue*) ; 
 scalar_t__ rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int macvtap_set_queue(struct net_device *dev, struct file *file,
				struct macvtap_queue *q)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	int err = -EBUSY;

	rtnl_lock();
	if (rtnl_dereference(vlan->tap))
		goto out;

	err = 0;
	rcu_assign_pointer(q->vlan, vlan);
	rcu_assign_pointer(vlan->tap, q);
	sock_hold(&q->sk);

	q->file = file;
	file->private_data = q;

out:
	rtnl_unlock();
	return err;
}