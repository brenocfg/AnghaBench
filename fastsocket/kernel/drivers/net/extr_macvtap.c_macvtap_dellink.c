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
struct macvlan_dev {int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_dellink (struct net_device*) ; 
 int /*<<< orphan*/  macvtap_class ; 
 int /*<<< orphan*/  macvtap_del_queues (struct net_device*) ; 
 int /*<<< orphan*/  macvtap_free_minor (struct macvlan_dev*) ; 
 int /*<<< orphan*/  macvtap_major ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void macvtap_dellink(struct net_device *dev)
{
	struct macvlan_dev *vlan;

	vlan = netdev_priv(dev);
	device_destroy(macvtap_class,
		       MKDEV(MAJOR(macvtap_major), vlan->minor));

	macvtap_del_queues(dev);
	macvlan_dellink(dev);
	macvtap_free_minor(vlan);
}