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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct bonding {int /*<<< orphan*/  lock; int /*<<< orphan*/  curr_slave_lock; TYPE_1__* curr_active_slave; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_IS_OK (struct bonding*) ; 
 int NETDEV_TX_OK ; 
 int bond_dev_queue_xmit (struct bonding*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bond_xmit_activebackup(struct sk_buff *skb, struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	int res = 1;

	read_lock(&bond->lock);
	read_lock(&bond->curr_slave_lock);

	if (!BOND_IS_OK(bond))
		goto out;

	if (!bond->curr_active_slave)
		goto out;

	res = bond_dev_queue_xmit(bond, skb, bond->curr_active_slave->dev);

out:
	if (res)
		/* no suitable interface, frame not sent */
		dev_kfree_skb(skb);

	read_unlock(&bond->curr_slave_lock);
	read_unlock(&bond->lock);
	return NETDEV_TX_OK;
}