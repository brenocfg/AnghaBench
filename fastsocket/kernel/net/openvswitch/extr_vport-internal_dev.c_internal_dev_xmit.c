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
struct TYPE_2__ {int /*<<< orphan*/  vport; } ;

/* Variables and functions */
 TYPE_1__* internal_dev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ovs_vport_receive (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int internal_dev_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	rcu_read_lock();
	ovs_vport_receive(internal_dev_priv(netdev)->vport, skb, NULL);
	rcu_read_unlock();
	return 0;
}