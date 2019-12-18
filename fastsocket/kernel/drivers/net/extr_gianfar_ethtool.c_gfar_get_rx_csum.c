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
typedef  int /*<<< orphan*/  uint32_t ;
struct net_device {int dummy; } ;
struct gfar_private {int device_flags; int /*<<< orphan*/  rx_csum_enable; } ;

/* Variables and functions */
 int FSL_GIANFAR_DEV_HAS_CSUM ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static uint32_t gfar_get_rx_csum(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);

	if (!(priv->device_flags & FSL_GIANFAR_DEV_HAS_CSUM))
		return 0;

	return priv->rx_csum_enable;
}