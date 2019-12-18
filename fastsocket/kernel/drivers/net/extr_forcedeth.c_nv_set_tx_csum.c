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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct fe_priv {int driver_data; } ;

/* Variables and functions */
 int DEV_HAS_CHECKSUM ; 
 int EOPNOTSUPP ; 
 int ethtool_op_set_tx_csum (struct net_device*,int /*<<< orphan*/ ) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nv_set_tx_csum(struct net_device *dev, u32 data)
{
	struct fe_priv *np = netdev_priv(dev);

	if (np->driver_data & DEV_HAS_CHECKSUM)
		return ethtool_op_set_tx_csum(dev, data);
	else
		return -EOPNOTSUPP;
}