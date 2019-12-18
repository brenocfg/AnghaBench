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
struct stmmac_priv {int /*<<< orphan*/  is_gmac; } ;
struct net_device {scalar_t__ base_addr; } ;
struct ethtool_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_BUS_MODE ; 
 scalar_t__ DMA_CUR_RX_BUF_ADDR ; 
 scalar_t__ DMA_CUR_TX_BUF_ADDR ; 
 int /*<<< orphan*/  REG_SPACE_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

void stmmac_ethtool_gregs(struct net_device *dev,
			  struct ethtool_regs *regs, void *space)
{
	int i;
	u32 *reg_space = (u32 *) space;

	struct stmmac_priv *priv = netdev_priv(dev);

	memset(reg_space, 0x0, REG_SPACE_SIZE);

	if (!priv->is_gmac) {
		/* MAC registers */
		for (i = 0; i < 12; i++)
			reg_space[i] = readl(dev->base_addr + (i * 4));
		/* DMA registers */
		for (i = 0; i < 9; i++)
			reg_space[i + 12] =
			    readl(dev->base_addr + (DMA_BUS_MODE + (i * 4)));
		reg_space[22] = readl(dev->base_addr + DMA_CUR_TX_BUF_ADDR);
		reg_space[23] = readl(dev->base_addr + DMA_CUR_RX_BUF_ADDR);
	} else {
		/* MAC registers */
		for (i = 0; i < 55; i++)
			reg_space[i] = readl(dev->base_addr + (i * 4));
		/* DMA registers */
		for (i = 0; i < 22; i++)
			reg_space[i + 55] =
			    readl(dev->base_addr + (DMA_BUS_MODE + (i * 4)));
	}

	return;
}