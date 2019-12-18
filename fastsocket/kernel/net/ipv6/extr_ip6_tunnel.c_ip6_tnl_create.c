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
struct net {int dummy; } ;
struct ip6_tnl_parm {scalar_t__* name; } ;
struct ip6_tnl_net {int dummy; } ;
struct ip6_tnl {struct ip6_tnl_parm parms; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_alloc_name (struct net_device*,char*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ip6_tnl_dev_init (struct net_device*) ; 
 int /*<<< orphan*/  ip6_tnl_dev_setup ; 
 int /*<<< orphan*/  ip6_tnl_link (struct ip6_tnl_net*,struct ip6_tnl*) ; 
 int /*<<< orphan*/  ip6_tnl_net_id ; 
 struct ip6_tnl_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__*,int) ; 

__attribute__((used)) static struct ip6_tnl *ip6_tnl_create(struct net *net, struct ip6_tnl_parm *p)
{
	struct net_device *dev;
	struct ip6_tnl *t;
	char name[IFNAMSIZ];
	int err;
	struct ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	if (p->name[0])
		strlcpy(name, p->name, IFNAMSIZ);
	else
		sprintf(name, "ip6tnl%%d");

	dev = alloc_netdev(sizeof (*t), name, ip6_tnl_dev_setup);
	if (dev == NULL)
		goto failed;

	dev_net_set(dev, net);

	if (strchr(name, '%')) {
		if (dev_alloc_name(dev, name) < 0)
			goto failed_free;
	}

	t = netdev_priv(dev);
	t->parms = *p;
	ip6_tnl_dev_init(dev);

	if ((err = register_netdevice(dev)) < 0)
		goto failed_free;

	dev_hold(dev);
	ip6_tnl_link(ip6n, t);
	return t;

failed_free:
	free_netdev(dev);
failed:
	return NULL;
}