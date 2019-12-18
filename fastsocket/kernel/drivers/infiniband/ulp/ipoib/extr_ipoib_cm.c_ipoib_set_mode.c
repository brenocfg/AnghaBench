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
struct net_device {int features; int /*<<< orphan*/  mtu; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  send_flags; } ;
struct ipoib_dev_priv {int hca_caps; int /*<<< orphan*/  mcast_mtu; TYPE_2__* dev; int /*<<< orphan*/  flags; TYPE_1__ tx_wr; } ;
struct TYPE_4__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_DEVICE_UD_TSO ; 
 int /*<<< orphan*/  IB_SEND_IP_CSUM ; 
 scalar_t__ IPOIB_CM_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPOIB_FLAG_ADMIN_CM ; 
 int /*<<< orphan*/  IPOIB_FLAG_CSUM ; 
 int /*<<< orphan*/  NETIF_F_GRO ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_flush_paths (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipoib_set_mode(struct net_device *dev, const char *buf)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);

	/* flush paths if we switch modes so that connections are restarted */
	if (IPOIB_CM_SUPPORTED(dev->dev_addr) && !strcmp(buf, "connected\n")) {
		set_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
		ipoib_warn(priv, "enabling connected mode "
			   "will cause multicast packet drops\n");

		dev->features &= ~(NETIF_F_IP_CSUM | NETIF_F_SG | NETIF_F_TSO);
		rtnl_unlock();
		priv->tx_wr.send_flags &= ~IB_SEND_IP_CSUM;

		ipoib_flush_paths(dev);
		rtnl_lock();
		return 0;
	}

	if (!strcmp(buf, "datagram\n")) {
		clear_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);

		if (test_bit(IPOIB_FLAG_CSUM, &priv->flags)) {
			dev->features |= NETIF_F_IP_CSUM | NETIF_F_SG;
			priv->dev->features |= NETIF_F_GRO;
			if (priv->hca_caps & IB_DEVICE_UD_TSO)
				dev->features |= NETIF_F_TSO;
		}
		dev_set_mtu(dev, min(priv->mcast_mtu, dev->mtu));
		rtnl_unlock();
		ipoib_flush_paths(dev);
		rtnl_lock();
		return 0;
	}

	return -EINVAL;
}