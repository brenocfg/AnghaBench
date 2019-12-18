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
struct pch_gbe_adapter {int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int generic_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int pch_gbe_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);

	pr_debug("cmd : 0x%04x\n", cmd);

	return generic_mii_ioctl(&adapter->mii, if_mii(ifr), cmd, NULL);
}