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
struct rtl8169_private {size_t mac_version; } ;
struct net_device {int mtu; int features; } ;
struct TYPE_2__ {int jumbo_max; int /*<<< orphan*/  jumbo_tx_csum; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_DATA_LEN ; 
 int ETH_ZLEN ; 
 int JUMBO_1K ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETIF_F_TSO_ECN ; 
 int TD_MSS_MAX ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 TYPE_1__* rtl_chip_infos ; 
 int /*<<< orphan*/  rtl_hw_jumbo_disable (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_jumbo_enable (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl8169_change_mtu(struct net_device *dev, int new_mtu)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (new_mtu < ETH_ZLEN ||
	    new_mtu > rtl_chip_infos[tp->mac_version].jumbo_max)
		return -EINVAL;

	if (new_mtu > ETH_DATA_LEN)
		rtl_hw_jumbo_enable(tp);
	else
		rtl_hw_jumbo_disable(tp);

	dev->mtu = new_mtu;

	if (dev->mtu > TD_MSS_MAX)
		dev->features &= ~(NETIF_F_TSO | NETIF_F_TSO6 |
				   NETIF_F_TSO_ECN);

	if (dev->mtu > JUMBO_1K &&
	    !rtl_chip_infos[tp->mac_version].jumbo_tx_csum)
		dev->features &= ~NETIF_F_IP_CSUM;

	return 0;
}