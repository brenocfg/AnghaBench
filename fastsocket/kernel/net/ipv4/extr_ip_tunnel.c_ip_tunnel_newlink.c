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
struct net_device {scalar_t__ type; int mtu; } ;
struct net {int dummy; } ;
struct ip_tunnel_parm {int dummy; } ;
struct ip_tunnel_net {int dummy; } ;
struct ip_tunnel {struct ip_tunnel_parm parms; int /*<<< orphan*/  ip_tnl_net_id; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EEXIST ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_MTU ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ip_tunnel_add (struct ip_tunnel_net*,struct ip_tunnel*) ; 
 int ip_tunnel_bind_dev (struct net_device*) ; 
 scalar_t__ ip_tunnel_find (struct ip_tunnel_net*,struct ip_tunnel_parm*,scalar_t__) ; 
 struct ip_tunnel_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 

int ip_tunnel_newlink(struct net_device *dev, struct nlattr *tb[],
		      struct ip_tunnel_parm *p)
{
	struct ip_tunnel *nt;
	struct net *net = dev_net(dev);
	struct ip_tunnel_net *itn;
	int mtu;
	int err;

	nt = netdev_priv(dev);
	itn = net_generic(net, nt->ip_tnl_net_id);

	if (ip_tunnel_find(itn, p, dev->type))
		return -EEXIST;

	nt->parms = *p;
	err = register_netdevice(dev);
	if (err)
		goto out;

	if (dev->type == ARPHRD_ETHER && !tb[IFLA_ADDRESS])
		eth_hw_addr_random(dev);

	mtu = ip_tunnel_bind_dev(dev);
	if (!tb[IFLA_MTU])
		dev->mtu = mtu;

	ip_tunnel_add(itn, nt);

out:
	return err;
}