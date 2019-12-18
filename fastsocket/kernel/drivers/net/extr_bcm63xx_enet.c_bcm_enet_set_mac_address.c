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
typedef  int u32 ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int* dev_addr; } ;
struct bcm_enet_priv {int dummy; } ;

/* Variables and functions */
 int ENET_PMH_DATAVALID_MASK ; 
 int /*<<< orphan*/  ENET_PMH_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENET_PML_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  enet_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcm_enet_set_mac_address(struct net_device *dev, void *p)
{
	struct bcm_enet_priv *priv;
	struct sockaddr *addr = p;
	u32 val;

	priv = netdev_priv(dev);
	memcpy(dev->dev_addr, addr->sa_data, ETH_ALEN);

	/* use perfect match register 0 to store my mac address */
	val = (dev->dev_addr[2] << 24) | (dev->dev_addr[3] << 16) |
		(dev->dev_addr[4] << 8) | dev->dev_addr[5];
	enet_writel(priv, val, ENET_PML_REG(0));

	val = (dev->dev_addr[0] << 8 | dev->dev_addr[1]);
	val |= ENET_PMH_DATAVALID_MASK;
	enet_writel(priv, val, ENET_PMH_REG(0));

	return 0;
}