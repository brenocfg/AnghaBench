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
struct r8180_priv {int dma_poll_mask; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  EPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  TX_DMA_POLLING ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8180_set_mode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8180_dma_kick(struct net_device *dev, int priority)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	rtl8180_set_mode(dev,EPROM_CMD_CONFIG);
	write_nic_byte(dev, TX_DMA_POLLING,
			(1 << (priority + 1)) | priv->dma_poll_mask);
	rtl8180_set_mode(dev,EPROM_CMD_NORMAL);

	force_pci_posting(dev);
}