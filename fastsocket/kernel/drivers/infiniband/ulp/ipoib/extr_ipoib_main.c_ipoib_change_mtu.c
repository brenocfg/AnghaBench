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
struct net_device {int mtu; } ;
struct ipoib_dev_priv {int mcast_mtu; int admin_mtu; int /*<<< orphan*/  max_ib_mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPOIB_UD_MTU (int /*<<< orphan*/ ) ; 
 scalar_t__ ipoib_cm_admin_enabled (struct net_device*) ; 
 int ipoib_cm_max_mtu (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 int min (int,int) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ipoib_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);

	/* dev->mtu > 2K ==> connected mode */
	if (ipoib_cm_admin_enabled(dev)) {
		if (new_mtu > ipoib_cm_max_mtu(dev))
			return -EINVAL;

		if (new_mtu > priv->mcast_mtu)
			ipoib_warn(priv, "mtu > %d will cause multicast packet drops.\n",
				   priv->mcast_mtu);

		dev->mtu = new_mtu;
		return 0;
	}

	if (new_mtu > IPOIB_UD_MTU(priv->max_ib_mtu))
		return -EINVAL;

	priv->admin_mtu = new_mtu;

	dev->mtu = min(priv->mcast_mtu, priv->admin_mtu);

	return 0;
}