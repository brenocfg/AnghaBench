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
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct ks8851_net {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  KS_MAR (int) ; 
 int /*<<< orphan*/  ks8851_wrreg8 (struct ks8851_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ks8851_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks8851_write_mac_addr(struct net_device *dev)
{
	struct ks8851_net *ks = netdev_priv(dev);
	int i;

	mutex_lock(&ks->lock);

	for (i = 0; i < ETH_ALEN; i++)
		ks8851_wrreg8(ks, KS_MAR(i), dev->dev_addr[i]);

	mutex_unlock(&ks->lock);

	return 0;
}