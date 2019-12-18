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
struct tsi108_prv_data {int /*<<< orphan*/  txlock; int /*<<< orphan*/  mii_if; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tsi108_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct tsi108_prv_data *data = netdev_priv(dev);
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&data->txlock, flags);
	rc = mii_ethtool_gset(&data->mii_if, cmd);
	spin_unlock_irqrestore(&data->txlock, flags);

	return rc;
}