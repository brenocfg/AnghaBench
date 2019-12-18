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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct macvtap_queue {int dummy; } ;
struct macvlan_dev {int /*<<< orphan*/  tap; } ;

/* Variables and functions */
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 struct macvtap_queue* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct macvtap_queue *macvtap_get_queue(struct net_device *dev,
					       struct sk_buff *skb)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	return rcu_dereference(vlan->tap);
}