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
struct net_device {int dummy; } ;
struct cas {int mac_rx_cfg; int /*<<< orphan*/  lock; scalar_t__ regs; int /*<<< orphan*/  hw_running; } ;

/* Variables and functions */
 int MAC_RX_CFG_EN ; 
 int MAC_RX_CFG_HASH_FILTER_EN ; 
 int MAC_RX_CFG_PROMISC_EN ; 
 scalar_t__ REG_MAC_RX_CFG ; 
 int STOP_TRIES ; 
 int cas_setup_multicast (struct cas*) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cas_set_multicast(struct net_device *dev)
{
	struct cas *cp = netdev_priv(dev);
	u32 rxcfg, rxcfg_new;
	unsigned long flags;
	int limit = STOP_TRIES;

	if (!cp->hw_running)
		return;

	spin_lock_irqsave(&cp->lock, flags);
	rxcfg = readl(cp->regs + REG_MAC_RX_CFG);

	/* disable RX MAC and wait for completion */
	writel(rxcfg & ~MAC_RX_CFG_EN, cp->regs + REG_MAC_RX_CFG);
	while (readl(cp->regs + REG_MAC_RX_CFG) & MAC_RX_CFG_EN) {
		if (!limit--)
			break;
		udelay(10);
	}

	/* disable hash filter and wait for completion */
	limit = STOP_TRIES;
	rxcfg &= ~(MAC_RX_CFG_PROMISC_EN | MAC_RX_CFG_HASH_FILTER_EN);
	writel(rxcfg & ~MAC_RX_CFG_EN, cp->regs + REG_MAC_RX_CFG);
	while (readl(cp->regs + REG_MAC_RX_CFG) & MAC_RX_CFG_HASH_FILTER_EN) {
		if (!limit--)
			break;
		udelay(10);
	}

	/* program hash filters */
	cp->mac_rx_cfg = rxcfg_new = cas_setup_multicast(cp);
	rxcfg |= rxcfg_new;
	writel(rxcfg, cp->regs + REG_MAC_RX_CFG);
	spin_unlock_irqrestore(&cp->lock, flags);
}