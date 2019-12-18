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
struct rtnl_link_ops {int /*<<< orphan*/  setup; int /*<<< orphan*/  priv_size; scalar_t__* kind; } ;
struct net_device {struct rtnl_link_ops const* rtnl_link_ops; } ;
struct net {int dummy; } ;
struct ip_tunnel_parm {scalar_t__* name; } ;
struct ip_tunnel {struct ip_tunnel_parm parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int E2BIG ; 
 int ENOMEM ; 
 struct net_device* ERR_PTR (int) ; 
 int IFNAMSIZ ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dev_alloc_name (struct net_device*,char*) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__*,int) ; 
 int strlen (scalar_t__*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static struct net_device *__ip_tunnel_create(struct net *net,
					     const struct rtnl_link_ops *ops,
					     struct ip_tunnel_parm *parms)
{
	int err;
	struct ip_tunnel *tunnel;
	struct net_device *dev;
	char name[IFNAMSIZ];

	if (parms->name[0])
		strlcpy(name, parms->name, IFNAMSIZ);
	else {
		if (strlen(ops->kind) > (IFNAMSIZ - 3)) {
			err = -E2BIG;
			goto failed;
		}
		strlcpy(name, ops->kind, IFNAMSIZ);
		strncat(name, "%d", 2);
	}

	ASSERT_RTNL();
	dev = alloc_netdev(ops->priv_size, name, ops->setup);
	if (!dev) {
		err = -ENOMEM;
		goto failed;
	}
	dev_net_set(dev, net);

	if (strchr(name, '%')) {
		err = dev_alloc_name(dev, name);
		if (err < 0)
			goto failed;
	}

	dev->rtnl_link_ops = ops;

	tunnel = netdev_priv(dev);
	tunnel->parms = *parms;

	err = register_netdevice(dev);
	if (err)
		goto failed_free;

	return dev;

failed_free:
	free_netdev(dev);
failed:
	return ERR_PTR(err);
}