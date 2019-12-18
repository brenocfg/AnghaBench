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
struct net_device {int /*<<< orphan*/ * ip_ptr; } ;
struct in_ifaddr {int dummy; } ;
struct in_device {int dead; int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  arp_parms; struct in_ifaddr* ifa_list; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  arp_ifdown (struct net_device*) ; 
 int /*<<< orphan*/  arp_tbl ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devinet_sysctl_unregister (struct in_device*) ; 
 int /*<<< orphan*/  in_dev_rcu_put ; 
 int /*<<< orphan*/  inet_del_ifa (struct in_device*,struct in_ifaddr**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_free_ifa (struct in_ifaddr*) ; 
 int /*<<< orphan*/  ip_mc_destroy_dev (struct in_device*) ; 
 int /*<<< orphan*/  neigh_parms_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inetdev_destroy(struct in_device *in_dev)
{
	struct in_ifaddr *ifa;
	struct net_device *dev;

	ASSERT_RTNL();

	dev = in_dev->dev;

	in_dev->dead = 1;

	ip_mc_destroy_dev(in_dev);

	while ((ifa = in_dev->ifa_list) != NULL) {
		inet_del_ifa(in_dev, &in_dev->ifa_list, 0);
		inet_free_ifa(ifa);
	}

	dev->ip_ptr = NULL;

	devinet_sysctl_unregister(in_dev);
	neigh_parms_release(&arp_tbl, in_dev->arp_parms);
	arp_ifdown(dev);

	call_rcu(&in_dev->rcu_head, in_dev_rcu_put);
}