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
struct net_device {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  feature_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_SG ; 
 int /*<<< orphan*/  br_features_recompute (struct net_bridge*) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int br_set_sg(struct net_device *dev, u32 data)
{
	struct net_bridge *br = netdev_priv(dev);

	if (data)
		br->feature_mask |= NETIF_F_SG;
	else
		br->feature_mask &= ~NETIF_F_SG;

	br_features_recompute(br);
	return 0;
}