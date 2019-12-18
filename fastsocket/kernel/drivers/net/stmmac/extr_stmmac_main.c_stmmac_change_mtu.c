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
struct stmmac_priv {scalar_t__ is_gmac; } ;
struct net_device {int mtu; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ETH_DATA_LEN ; 
 int JUMBO_LEN ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int stmmac_change_mtu(struct net_device *dev, int new_mtu)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int max_mtu;

	if (netif_running(dev)) {
		pr_err("%s: must be stopped to change its MTU\n", dev->name);
		return -EBUSY;
	}

	if (priv->is_gmac)
		max_mtu = JUMBO_LEN;
	else
		max_mtu = ETH_DATA_LEN;

	if ((new_mtu < 46) || (new_mtu > max_mtu)) {
		pr_err("%s: invalid MTU, max MTU is: %d\n", dev->name, max_mtu);
		return -EINVAL;
	}

	dev->mtu = new_mtu;

	return 0;
}