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
struct veth_priv {int /*<<< orphan*/  ip_summed; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int veth_set_rx_csum(struct net_device *dev, u32 data)
{
	struct veth_priv *priv;

	priv = netdev_priv(dev);
	priv->ip_summed = data ? CHECKSUM_UNNECESSARY : CHECKSUM_NONE;
	return 0;
}