#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int maxvif; int mroute_reg_vif_num; struct mif_device* vif6_table; } ;
struct net {TYPE_1__ ipv6; } ;
struct mif_device {int flags; struct net_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  mc_forwarding; } ;
struct inet6_dev {TYPE_2__ cnf; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int MIFF_REGISTER ; 
 scalar_t__ MIF_EXISTS (struct net*,int) ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  mrt_lock ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mif6_delete(struct net *net, int vifi)
{
	struct mif_device *v;
	struct net_device *dev;
	struct inet6_dev *in6_dev;
	if (vifi < 0 || vifi >= net->ipv6.maxvif)
		return -EADDRNOTAVAIL;

	v = &net->ipv6.vif6_table[vifi];

	write_lock_bh(&mrt_lock);
	dev = v->dev;
	v->dev = NULL;

	if (!dev) {
		write_unlock_bh(&mrt_lock);
		return -EADDRNOTAVAIL;
	}

#ifdef CONFIG_IPV6_PIMSM_V2
	if (vifi == net->ipv6.mroute_reg_vif_num)
		net->ipv6.mroute_reg_vif_num = -1;
#endif

	if (vifi + 1 == net->ipv6.maxvif) {
		int tmp;
		for (tmp = vifi - 1; tmp >= 0; tmp--) {
			if (MIF_EXISTS(net, tmp))
				break;
		}
		net->ipv6.maxvif = tmp + 1;
	}

	write_unlock_bh(&mrt_lock);

	dev_set_allmulti(dev, -1);

	in6_dev = __in6_dev_get(dev);
	if (in6_dev)
		in6_dev->cnf.mc_forwarding--;

	if (v->flags & MIFF_REGISTER)
		unregister_netdevice(dev);

	dev_put(dev);
	return 0;
}