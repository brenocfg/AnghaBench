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
struct vlan_dev_info {int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  flags; struct net_device* real_dev; } ;
struct nlattr {int dummy; } ;
struct net_device {scalar_t__ mtu; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct net* src_net; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t IFLA_LINK ; 
 size_t IFLA_MTU ; 
 size_t IFLA_VLAN_ID ; 
 int /*<<< orphan*/  VLAN_FLAG_REORDER_HDR ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int register_vlan_dev (struct net_device*) ; 
 int vlan_changelink (struct net_device*,struct nlattr**,struct nlattr**) ; 
 int vlan_check_real_dev (struct net_device*,int /*<<< orphan*/ ) ; 
 struct vlan_dev_info* vlan_dev_info (struct net_device*) ; 

__attribute__((used)) static int vlan_newlink(struct net_device *dev,
			struct nlattr *tb[], struct nlattr *data[])
{
	struct vlan_dev_info *vlan = vlan_dev_info(dev);
	struct net_device *real_dev;
	struct net *src_net = netdev_extended(dev)->src_net;
	int err;

	if (!data[IFLA_VLAN_ID])
		return -EINVAL;

	if (!tb[IFLA_LINK])
		return -EINVAL;
	real_dev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	if (!real_dev)
		return -ENODEV;

	vlan->vlan_id  = nla_get_u16(data[IFLA_VLAN_ID]);
	vlan->real_dev = real_dev;
	vlan->flags    = VLAN_FLAG_REORDER_HDR;

	err = vlan_check_real_dev(real_dev, vlan->vlan_id);
	if (err < 0)
		return err;

	if (!tb[IFLA_MTU])
		dev->mtu = real_dev->mtu;
	else if (dev->mtu > real_dev->mtu)
		return -EINVAL;

	err = vlan_changelink(dev, tb, data);
	if (err < 0)
		return err;

	return register_vlan_dev(dev);
}