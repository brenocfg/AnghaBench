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
struct net_device {unsigned int flags; int /*<<< orphan*/  type; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  ttl; } ;
struct ip_tunnel_parm {int i_flags; int o_flags; TYPE_1__ iph; int /*<<< orphan*/  o_key; int /*<<< orphan*/  i_key; } ;
struct ip_tunnel_net {struct net_device* fb_tunnel_dev; } ;
struct ip_tunnel {struct net_device* dev; int /*<<< orphan*/  parms; int /*<<< orphan*/  ip_tnl_net_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int EPERM ; 
 unsigned int IFF_BROADCAST ; 
 unsigned int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IP_DF ; 
#define  SIOCADDTUNNEL 131 
#define  SIOCCHGTUNNEL 130 
#define  SIOCDELTUNNEL 129 
#define  SIOCGETTUNNEL 128 
 int TUNNEL_KEY ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ip_tunnel* ip_tunnel_create (struct net*,struct ip_tunnel_net*,struct ip_tunnel_parm*) ; 
 struct ip_tunnel* ip_tunnel_find (struct ip_tunnel_net*,struct ip_tunnel_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_tunnel_update (struct ip_tunnel_net*,struct ip_tunnel*,struct net_device*,struct ip_tunnel_parm*,int) ; 
 int /*<<< orphan*/  ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ip_tunnel_parm*,int /*<<< orphan*/ *,int) ; 
 struct ip_tunnel_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

int ip_tunnel_ioctl(struct net_device *dev, struct ip_tunnel_parm *p, int cmd)
{
	int err = 0;
	struct ip_tunnel *t;
	struct net *net = dev_net(dev);
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct ip_tunnel_net *itn = net_generic(net, tunnel->ip_tnl_net_id);

	BUG_ON(!itn->fb_tunnel_dev);
	switch (cmd) {
	case SIOCGETTUNNEL:
		t = NULL;
		if (dev == itn->fb_tunnel_dev)
			t = ip_tunnel_find(itn, p, itn->fb_tunnel_dev->type);
		if (t == NULL)
			t = netdev_priv(dev);
		memcpy(p, &t->parms, sizeof(*p));
		break;

	case SIOCADDTUNNEL:
	case SIOCCHGTUNNEL:
		err = -EPERM;
		if (!capable(CAP_NET_ADMIN))
			goto done;
		if (p->iph.ttl)
			p->iph.frag_off |= htons(IP_DF);
		if (!(p->i_flags&TUNNEL_KEY))
			p->i_key = 0;
		if (!(p->o_flags&TUNNEL_KEY))
			p->o_key = 0;

		t = ip_tunnel_find(itn, p, itn->fb_tunnel_dev->type);

		if (!t && (cmd == SIOCADDTUNNEL))
			t = ip_tunnel_create(net, itn, p);

		if (dev != itn->fb_tunnel_dev && cmd == SIOCCHGTUNNEL) {
			if (t != NULL) {
				if (t->dev != dev) {
					err = -EEXIST;
					break;
				}
			} else {
				unsigned int nflags = 0;

				if (ipv4_is_multicast(p->iph.daddr))
					nflags = IFF_BROADCAST;
				else if (p->iph.daddr)
					nflags = IFF_POINTOPOINT;

				if ((dev->flags^nflags)&(IFF_POINTOPOINT|IFF_BROADCAST)) {
					err = -EINVAL;
					break;
				}

				t = netdev_priv(dev);
			}
		}

		if (t) {
			err = 0;
			ip_tunnel_update(itn, t, dev, p, true);
		} else
			err = (cmd == SIOCADDTUNNEL ? -ENOBUFS : -ENOENT);
		break;

	case SIOCDELTUNNEL:
		err = -EPERM;
		if (!capable(CAP_NET_ADMIN))
			goto done;

		if (dev == itn->fb_tunnel_dev) {
			err = -ENOENT;
			t = ip_tunnel_find(itn, p, itn->fb_tunnel_dev->type);
			if (t == NULL)
				goto done;
			err = -EPERM;
			if (t == netdev_priv(itn->fb_tunnel_dev))
				goto done;
			dev = t->dev;
		}
		unregister_netdevice(dev);
		err = 0;
		break;

	default:
		err = -EINVAL;
	}

done:
	return err;
}