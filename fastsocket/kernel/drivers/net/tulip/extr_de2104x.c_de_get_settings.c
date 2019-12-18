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
struct ethtool_cmd {int dummy; } ;
struct de_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __de_get_settings (struct de_private*,struct ethtool_cmd*) ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int de_get_settings(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	struct de_private *de = netdev_priv(dev);
	int rc;

	spin_lock_irq(&de->lock);
	rc = __de_get_settings(de, ecmd);
	spin_unlock_irq(&de->lock);

	return rc;
}