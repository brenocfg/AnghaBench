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
struct gfar_private {int device_flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int FSL_GIANFAR_DEV_HAS_RMON ; 
 int GFAR_EXTRA_STATS_LEN ; 
 int GFAR_STATS_LEN ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gfar_sset_count(struct net_device *dev, int sset)
{
	struct gfar_private *priv = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		if (priv->device_flags & FSL_GIANFAR_DEV_HAS_RMON)
			return GFAR_STATS_LEN;
		else
			return GFAR_EXTRA_STATS_LEN;
	default:
		return -EOPNOTSUPP;
	}
}