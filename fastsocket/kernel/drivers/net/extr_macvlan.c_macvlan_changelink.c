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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct macvlan_dev {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 size_t IFLA_MACVLAN_MODE ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int macvlan_changelink(struct net_device *dev,
		struct nlattr *tb[], struct nlattr *data[])
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	if (data && data[IFLA_MACVLAN_MODE])
		vlan->mode = nla_get_u32(data[IFLA_MACVLAN_MODE]);
	return 0;
}