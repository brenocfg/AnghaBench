#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; int /*<<< orphan*/  ip_ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sysctl; } ;
struct in_device {TYPE_2__ cnf; int /*<<< orphan*/ * arp_parms; struct net_device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  devconf_dflt; } ;
struct TYPE_7__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  FORWARDING ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_UP ; 
 scalar_t__ IPV4_DEVCONF (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arp_tbl ; 
 int /*<<< orphan*/  dev_disable_lro (struct net_device*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 TYPE_3__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  devinet_sysctl_register (struct in_device*) ; 
 int /*<<< orphan*/  in_dev_hold (struct in_device*) ; 
 int /*<<< orphan*/  ip_mc_init_dev (struct in_device*) ; 
 int /*<<< orphan*/  ip_mc_up (struct in_device*) ; 
 int /*<<< orphan*/  kfree (struct in_device*) ; 
 struct in_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * neigh_parms_alloc (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct in_device*) ; 

__attribute__((used)) static struct in_device *inetdev_init(struct net_device *dev)
{
	struct in_device *in_dev;

	ASSERT_RTNL();

	in_dev = kzalloc(sizeof(*in_dev), GFP_KERNEL);
	if (!in_dev)
		goto out;
	memcpy(&in_dev->cnf, dev_net(dev)->ipv4.devconf_dflt,
			sizeof(in_dev->cnf));

	in_dev->cnf.sysctl = NULL;
	in_dev->dev = dev;
	if ((in_dev->arp_parms = neigh_parms_alloc(dev, &arp_tbl)) == NULL)
		goto out_kfree;
	if (IPV4_DEVCONF(in_dev->cnf, FORWARDING))
		dev_disable_lro(dev);
	/* Reference in_dev->dev */
	dev_hold(dev);
	/* Account for reference dev->ip_ptr (below) */
	in_dev_hold(in_dev);

	devinet_sysctl_register(in_dev);
	ip_mc_init_dev(in_dev);
	if (dev->flags & IFF_UP)
		ip_mc_up(in_dev);

	/* we can receive as soon as ip_ptr is set -- do this last */
	rcu_assign_pointer(dev->ip_ptr, in_dev);
out:
	return in_dev;
out_kfree:
	kfree(in_dev);
	in_dev = NULL;
	goto out;
}