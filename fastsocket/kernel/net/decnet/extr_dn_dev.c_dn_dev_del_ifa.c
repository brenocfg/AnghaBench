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
struct net_device {scalar_t__ type; int /*<<< orphan*/  dev_addr; } ;
struct dn_ifaddr {scalar_t__ ifa_local; struct dn_ifaddr* ifa_next; } ;
struct dn_dev {struct net_device* dev; int /*<<< orphan*/ * ifa_list; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NETDEV_DOWN ; 
 int /*<<< orphan*/  RTM_DELADDR ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dn_ifaddr*) ; 
 int /*<<< orphan*/  dev_mc_delete (struct net_device*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_dev_delete (struct net_device*) ; 
 int /*<<< orphan*/  dn_dev_free_ifa (struct dn_ifaddr*) ; 
 int /*<<< orphan*/  dn_dn2eth (unsigned char*,scalar_t__) ; 
 scalar_t__ dn_eth2dn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_ifaddr_notify (int /*<<< orphan*/ ,struct dn_ifaddr*) ; 
 int /*<<< orphan*/  dnaddr_chain ; 

__attribute__((used)) static void dn_dev_del_ifa(struct dn_dev *dn_db, struct dn_ifaddr **ifap, int destroy)
{
	struct dn_ifaddr *ifa1 = *ifap;
	unsigned char mac_addr[6];
	struct net_device *dev = dn_db->dev;

	ASSERT_RTNL();

	*ifap = ifa1->ifa_next;

	if (dn_db->dev->type == ARPHRD_ETHER) {
		if (ifa1->ifa_local != dn_eth2dn(dev->dev_addr)) {
			dn_dn2eth(mac_addr, ifa1->ifa_local);
			dev_mc_delete(dev, mac_addr, ETH_ALEN, 0);
		}
	}

	dn_ifaddr_notify(RTM_DELADDR, ifa1);
	blocking_notifier_call_chain(&dnaddr_chain, NETDEV_DOWN, ifa1);
	if (destroy) {
		dn_dev_free_ifa(ifa1);

		if (dn_db->ifa_list == NULL)
			dn_dev_delete(dn_db->dev);
	}
}