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
struct net_device {int /*<<< orphan*/  features; } ;
struct bnad {int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_IPV6_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnad_set_tx_csum(struct net_device *netdev, u32 tx_csum)
{
	struct bnad *bnad = netdev_priv(netdev);

	mutex_lock(&bnad->conf_mutex);
	if (tx_csum) {
		netdev->features |= NETIF_F_IP_CSUM;
		netdev->features |= NETIF_F_IPV6_CSUM;
	} else {
		netdev->features &= ~NETIF_F_IP_CSUM;
		netdev->features &= ~NETIF_F_IPV6_CSUM;
	}
	mutex_unlock(&bnad->conf_mutex);
	return 0;
}