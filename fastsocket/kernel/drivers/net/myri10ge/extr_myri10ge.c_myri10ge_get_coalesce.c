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
struct net_device {int dummy; } ;
struct myri10ge_priv {int /*<<< orphan*/  intr_coal_delay; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
myri10ge_get_coalesce(struct net_device *netdev, struct ethtool_coalesce *coal)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);

	coal->rx_coalesce_usecs = mgp->intr_coal_delay;
	return 0;
}