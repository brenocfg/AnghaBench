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
struct net_device {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  dev; } ;
struct macvlan_dev {int /*<<< orphan*/  tap_features; int /*<<< orphan*/  minor; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  TUN_OFFLOADS ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int macvlan_common_newlink (struct net_device*,struct nlattr**,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvtap_class ; 
 int /*<<< orphan*/  macvtap_del_queues (struct net_device*) ; 
 int /*<<< orphan*/  macvtap_forward ; 
 int /*<<< orphan*/  macvtap_free_minor (struct macvlan_dev*) ; 
 int macvtap_get_minor (struct macvlan_dev*) ; 
 int /*<<< orphan*/  macvtap_major ; 
 int /*<<< orphan*/  macvtap_receive ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int notifier_from_errno (int) ; 

__attribute__((used)) static int macvtap_newlink(struct net_device *dev,
			   struct nlattr *tb[],
			   struct nlattr *data[])
{
	struct device *classdev;
	struct macvlan_dev *vlan;
	dev_t devt;
	int err;

	err = macvlan_common_newlink(dev, tb, data,
				     macvtap_receive, macvtap_forward);
	if (err)
		goto out;

	vlan = netdev_priv(dev);
	err = macvtap_get_minor(vlan);
	if (err)
		return notifier_from_errno(err);

	devt = MKDEV(MAJOR(macvtap_major), vlan->minor);

	classdev = device_create(macvtap_class, &dev->dev, devt,
				 dev, "tap%d", dev->ifindex);
	if (IS_ERR(classdev)) {
		err = PTR_ERR(classdev);
		macvtap_del_queues(dev);
		macvtap_free_minor(vlan);
	}

	vlan->tap_features = TUN_OFFLOADS;

out:
	return err;
}