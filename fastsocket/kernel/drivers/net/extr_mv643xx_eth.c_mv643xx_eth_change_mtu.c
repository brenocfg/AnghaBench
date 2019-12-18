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
struct net_device {int mtu; int /*<<< orphan*/  dev; } ;
struct mv643xx_eth_private {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mv643xx_eth_open (struct net_device*) ; 
 int /*<<< orphan*/  mv643xx_eth_recalc_skb_size (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  mv643xx_eth_stop (struct net_device*) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  tx_set_rate (struct mv643xx_eth_private*,int,int) ; 

__attribute__((used)) static int mv643xx_eth_change_mtu(struct net_device *dev, int new_mtu)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);

	if (new_mtu < 64 || new_mtu > 9500)
		return -EINVAL;

	dev->mtu = new_mtu;
	mv643xx_eth_recalc_skb_size(mp);
	tx_set_rate(mp, 1000000000, 16777216);

	if (!netif_running(dev))
		return 0;

	/*
	 * Stop and then re-open the interface. This will allocate RX
	 * skbs of the new MTU.
	 * There is a possible danger that the open will not succeed,
	 * due to memory being full.
	 */
	mv643xx_eth_stop(dev);
	if (mv643xx_eth_open(dev)) {
		dev_printk(KERN_ERR, &dev->dev,
			   "fatal error on re-opening device after "
			   "MTU change\n");
	}

	return 0;
}