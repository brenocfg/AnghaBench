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
struct net_device_ops {int (* ndo_set_config ) (struct net_device*,int /*<<< orphan*/ *) ;int (* ndo_do_ioctl ) (struct net_device*,struct ifreq*,unsigned int) ;int /*<<< orphan*/  ndo_set_rx_mode; int /*<<< orphan*/  ndo_set_multicast_list; } ;
struct net_device {int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  type; struct net_device_ops* netdev_ops; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct ifreq {char* ifr_newname; int /*<<< orphan*/  ifr_qlen; TYPE_1__ ifr_hwaddr; int /*<<< orphan*/  ifr_map; int /*<<< orphan*/  ifr_mtu; int /*<<< orphan*/  ifr_flags; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  NETDEV_CHANGEADDR ; 
#define  SIOCADDMULTI 138 
 unsigned int SIOCBONDCHANGEACTIVE ; 
 unsigned int SIOCBONDENSLAVE ; 
 unsigned int SIOCBONDINFOQUERY ; 
 unsigned int SIOCBONDRELEASE ; 
 unsigned int SIOCBONDSETHWADDR ; 
 unsigned int SIOCBONDSLAVEINFOQUERY ; 
 unsigned int SIOCBRADDIF ; 
 unsigned int SIOCBRDELIF ; 
#define  SIOCDELMULTI 137 
 unsigned int SIOCDEVPRIVATE ; 
 unsigned int SIOCGMIIPHY ; 
 unsigned int SIOCGMIIREG ; 
#define  SIOCSHWTSTAMP 136 
#define  SIOCSIFFLAGS 135 
#define  SIOCSIFHWADDR 134 
#define  SIOCSIFHWBROADCAST 133 
#define  SIOCSIFMAP 132 
#define  SIOCSIFMETRIC 131 
#define  SIOCSIFMTU 130 
#define  SIOCSIFNAME 129 
#define  SIOCSIFTXQLEN 128 
 unsigned int SIOCSMIIREG ; 
 unsigned int SIOCWANDEV ; 
 struct net_device* __dev_get_by_name (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int dev_change_flags (struct net_device*,int /*<<< orphan*/ ) ; 
 int dev_change_name (struct net_device*,char*) ; 
 int dev_mc_add (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dev_mc_delete (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dev_set_mac_address (struct net_device*,TYPE_1__*) ; 
 int dev_set_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,size_t) ; 
 int net_hwtstamp_validate (struct ifreq*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ *) ; 
 int stub2 (struct net_device*,struct ifreq*,unsigned int) ; 

__attribute__((used)) static int dev_ifsioc(struct net *net, struct ifreq *ifr, unsigned int cmd)
{
	int err;
	struct net_device *dev = __dev_get_by_name(net, ifr->ifr_name);
	const struct net_device_ops *ops;

	if (!dev)
		return -ENODEV;

	ops = dev->netdev_ops;

	switch (cmd) {
	case SIOCSIFFLAGS:	/* Set interface flags */
		return dev_change_flags(dev, ifr->ifr_flags);

	case SIOCSIFMETRIC:	/* Set the metric on the interface
				   (currently unused) */
		return -EOPNOTSUPP;

	case SIOCSIFMTU:	/* Set the MTU of a device */
		return dev_set_mtu(dev, ifr->ifr_mtu);

	case SIOCSIFHWADDR:
		return dev_set_mac_address(dev, &ifr->ifr_hwaddr);

	case SIOCSIFHWBROADCAST:
		if (ifr->ifr_hwaddr.sa_family != dev->type)
			return -EINVAL;
		memcpy(dev->broadcast, ifr->ifr_hwaddr.sa_data,
		       min(sizeof ifr->ifr_hwaddr.sa_data, (size_t) dev->addr_len));
		call_netdevice_notifiers(NETDEV_CHANGEADDR, dev);
		return 0;

	case SIOCSIFMAP:
		if (ops->ndo_set_config) {
			if (!netif_device_present(dev))
				return -ENODEV;
			return ops->ndo_set_config(dev, &ifr->ifr_map);
		}
		return -EOPNOTSUPP;

	case SIOCADDMULTI:
		if ((!ops->ndo_set_multicast_list && !ops->ndo_set_rx_mode) ||
		    ifr->ifr_hwaddr.sa_family != AF_UNSPEC)
			return -EINVAL;
		if (!netif_device_present(dev))
			return -ENODEV;
		return dev_mc_add(dev, ifr->ifr_hwaddr.sa_data,
				  dev->addr_len, 1);

	case SIOCDELMULTI:
		if ((!ops->ndo_set_multicast_list && !ops->ndo_set_rx_mode) ||
		    ifr->ifr_hwaddr.sa_family != AF_UNSPEC)
			return -EINVAL;
		if (!netif_device_present(dev))
			return -ENODEV;
		return dev_mc_delete(dev, ifr->ifr_hwaddr.sa_data,
				     dev->addr_len, 1);

	case SIOCSIFTXQLEN:
		if (ifr->ifr_qlen < 0)
			return -EINVAL;
		dev->tx_queue_len = ifr->ifr_qlen;
		return 0;

	case SIOCSIFNAME:
		ifr->ifr_newname[IFNAMSIZ-1] = '\0';
		return dev_change_name(dev, ifr->ifr_newname);

	case SIOCSHWTSTAMP:
		err = net_hwtstamp_validate(ifr);
		if (err)
			return err;
		/* fall through */

	/*
	 *	Unknown or private ioctl
	 */
	default:
		if ((cmd >= SIOCDEVPRIVATE &&
		    cmd <= SIOCDEVPRIVATE + 15) ||
		    cmd == SIOCBONDENSLAVE ||
		    cmd == SIOCBONDRELEASE ||
		    cmd == SIOCBONDSETHWADDR ||
		    cmd == SIOCBONDSLAVEINFOQUERY ||
		    cmd == SIOCBONDINFOQUERY ||
		    cmd == SIOCBONDCHANGEACTIVE ||
		    cmd == SIOCGMIIPHY ||
		    cmd == SIOCGMIIREG ||
		    cmd == SIOCSMIIREG ||
		    cmd == SIOCBRADDIF ||
		    cmd == SIOCBRDELIF ||
		    cmd == SIOCSHWTSTAMP ||
		    cmd == SIOCWANDEV) {
			err = -EOPNOTSUPP;
			if (ops->ndo_do_ioctl) {
				if (netif_device_present(dev))
					err = ops->ndo_do_ioctl(dev, ifr, cmd);
				else
					err = -ENODEV;
			}
		} else
			err = -EINVAL;

	}
	return err;
}