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
typedef  scalar_t__ u32 ;
struct net_device {int mtu; int /*<<< orphan*/  features; } ;
struct jme_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_TXCSUM ; 
 int /*<<< orphan*/  NETIF_F_HW_CSUM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_set_tx_csum(struct net_device *netdev, u32 on)
{
	struct jme_adapter *jme = netdev_priv(netdev);

	if (on) {
		set_bit(JME_FLAG_TXCSUM, &jme->flags);
		if (netdev->mtu <= 1900)
			netdev->features |= NETIF_F_HW_CSUM;
	} else {
		clear_bit(JME_FLAG_TXCSUM, &jme->flags);
		netdev->features &= ~NETIF_F_HW_CSUM;
	}

	return 0;
}