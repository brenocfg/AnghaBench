#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stmmac_priv {scalar_t__ wolenabled; int /*<<< orphan*/  wolopts; struct mac_device_info* mac_type; scalar_t__ is_gmac; } ;
struct net_device {unsigned long base_addr; } ;
struct TYPE_2__ {scalar_t__ pmt; } ;
struct mac_device_info {TYPE_1__ hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ PMT_SUPPORTED ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 struct mac_device_info* gmac_setup (unsigned long) ; 
 struct mac_device_info* mac100_setup (unsigned long) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int stmmac_mac_device_setup(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	unsigned long ioaddr = dev->base_addr;

	struct mac_device_info *device;

	if (priv->is_gmac)
		device = gmac_setup(ioaddr);
	else
		device = mac100_setup(ioaddr);

	if (!device)
		return -ENOMEM;

	priv->mac_type = device;

	priv->wolenabled = priv->mac_type->hw.pmt;	/* PMT supported */
	if (priv->wolenabled == PMT_SUPPORTED)
		priv->wolopts = WAKE_MAGIC;		/* Magic Frame */

	return 0;
}