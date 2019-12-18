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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipip_net {int dummy; } ;
struct TYPE_2__ {scalar_t__ daddr; scalar_t__ saddr; } ;
struct ip_tunnel_parm {scalar_t__* name; TYPE_1__ iph; } ;
struct ip_tunnel {struct ip_tunnel_parm parms; struct ip_tunnel* next; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int IFNAMSIZ ; 
 struct ip_tunnel** __ipip_bucket (struct ipip_net*,struct ip_tunnel_parm*) ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_alloc_name (struct net_device*,char*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ipip_net_id ; 
 int /*<<< orphan*/  ipip_tunnel_init (struct net_device*) ; 
 int /*<<< orphan*/  ipip_tunnel_link (struct ipip_net*,struct ip_tunnel*) ; 
 int /*<<< orphan*/  ipip_tunnel_setup ; 
 struct ipip_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 scalar_t__ register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__*,int) ; 

__attribute__((used)) static struct ip_tunnel * ipip_tunnel_locate(struct net *net,
		struct ip_tunnel_parm *parms, int create)
{
	__be32 remote = parms->iph.daddr;
	__be32 local = parms->iph.saddr;
	struct ip_tunnel *t, **tp, *nt;
	struct net_device *dev;
	char name[IFNAMSIZ];
	struct ipip_net *ipn = net_generic(net, ipip_net_id);

	for (tp = __ipip_bucket(ipn, parms); (t = *tp) != NULL; tp = &t->next) {
		if (local == t->parms.iph.saddr && remote == t->parms.iph.daddr)
			return t;
	}
	if (!create)
		return NULL;

	if (parms->name[0])
		strlcpy(name, parms->name, IFNAMSIZ);
	else
		sprintf(name, "tunl%%d");

	dev = alloc_netdev(sizeof(*t), name, ipip_tunnel_setup);
	if (dev == NULL)
		return NULL;

	dev_net_set(dev, net);

	if (strchr(name, '%')) {
		if (dev_alloc_name(dev, name) < 0)
			goto failed_free;
	}

	nt = netdev_priv(dev);
	nt->parms = *parms;

	ipip_tunnel_init(dev);

	if (register_netdevice(dev) < 0)
		goto failed_free;

	dev_hold(dev);
	ipip_tunnel_link(ipn, nt);
	return nt;

failed_free:
	free_netdev(dev);
	return NULL;
}