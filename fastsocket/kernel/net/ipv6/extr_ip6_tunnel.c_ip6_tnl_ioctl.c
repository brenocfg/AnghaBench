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
struct ip6_tnl_parm {int /*<<< orphan*/  proto; } ;
struct ip6_tnl_net {struct net_device* fb_tnl_dev; } ;
struct ip6_tnl {struct net_device* dev; struct ip6_tnl_parm parms; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifru_data; } ;
struct ifreq {TYPE_1__ ifr_ifru; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EEXIST ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
#define  SIOCADDTUNNEL 131 
#define  SIOCCHGTUNNEL 130 
#define  SIOCDELTUNNEL 129 
#define  SIOCGETTUNNEL 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (struct ip6_tnl_parm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ ,struct ip6_tnl_parm*,int) ; 
 struct net* dev_net (struct net_device*) ; 
 int ip6_tnl_change (struct ip6_tnl*,struct ip6_tnl_parm*) ; 
 int /*<<< orphan*/  ip6_tnl_link (struct ip6_tnl_net*,struct ip6_tnl*) ; 
 struct ip6_tnl* ip6_tnl_locate (struct net*,struct ip6_tnl_parm*,int) ; 
 int /*<<< orphan*/  ip6_tnl_net_id ; 
 int /*<<< orphan*/  ip6_tnl_unlink (struct ip6_tnl_net*,struct ip6_tnl*) ; 
 int /*<<< orphan*/  memcpy (struct ip6_tnl_parm*,struct ip6_tnl_parm*,int) ; 
 struct ip6_tnl_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_state_change (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int
ip6_tnl_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	int err = 0;
	struct ip6_tnl_parm p;
	struct ip6_tnl *t = NULL;
	struct net *net = dev_net(dev);
	struct ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	switch (cmd) {
	case SIOCGETTUNNEL:
		if (dev == ip6n->fb_tnl_dev) {
			if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof (p))) {
				err = -EFAULT;
				break;
			}
			t = ip6_tnl_locate(net, &p, 0);
		}
		if (t == NULL)
			t = netdev_priv(dev);
		memcpy(&p, &t->parms, sizeof (p));
		if (copy_to_user(ifr->ifr_ifru.ifru_data, &p, sizeof (p))) {
			err = -EFAULT;
		}
		break;
	case SIOCADDTUNNEL:
	case SIOCCHGTUNNEL:
		err = -EPERM;
		if (!capable(CAP_NET_ADMIN))
			break;
		err = -EFAULT;
		if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof (p)))
			break;
		err = -EINVAL;
		if (p.proto != IPPROTO_IPV6 && p.proto != IPPROTO_IPIP &&
		    p.proto != 0)
			break;
		t = ip6_tnl_locate(net, &p, cmd == SIOCADDTUNNEL);
		if (dev != ip6n->fb_tnl_dev && cmd == SIOCCHGTUNNEL) {
			if (t != NULL) {
				if (t->dev != dev) {
					err = -EEXIST;
					break;
				}
			} else
				t = netdev_priv(dev);

			ip6_tnl_unlink(ip6n, t);
			err = ip6_tnl_change(t, &p);
			ip6_tnl_link(ip6n, t);
			netdev_state_change(dev);
		}
		if (t) {
			err = 0;
			if (copy_to_user(ifr->ifr_ifru.ifru_data, &t->parms, sizeof (p)))
				err = -EFAULT;

		} else
			err = (cmd == SIOCADDTUNNEL ? -ENOBUFS : -ENOENT);
		break;
	case SIOCDELTUNNEL:
		err = -EPERM;
		if (!capable(CAP_NET_ADMIN))
			break;

		if (dev == ip6n->fb_tnl_dev) {
			err = -EFAULT;
			if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof (p)))
				break;
			err = -ENOENT;
			if ((t = ip6_tnl_locate(net, &p, 0)) == NULL)
				break;
			err = -EPERM;
			if (t->dev == ip6n->fb_tnl_dev)
				break;
			dev = t->dev;
		}
		err = 0;
		unregister_netdevice(dev);
		break;
	default:
		err = -EINVAL;
	}
	return err;
}