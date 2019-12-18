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
struct macvlan_dev {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_MACVLAN_MODE ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int macvlan_fill_info(struct sk_buff *skb,
				const struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	NLA_PUT_U32(skb, IFLA_MACVLAN_MODE, vlan->mode);
	return 0;

nla_put_failure:
	return -EMSGSIZE;
}