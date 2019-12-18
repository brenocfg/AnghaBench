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
struct r8192_priv {int dma_poll_mask; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  EPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  TX_DMA_POLLING ; 
 int TX_DMA_STOP_LOWPRIORITY_SHIFT ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_set_mode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8192_data_hard_stop(struct net_device *dev)
{
	//FIXME !!
	#if 0
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	priv->dma_poll_mask |= (1<<TX_DMA_STOP_LOWPRIORITY_SHIFT);
	rtl8192_set_mode(dev,EPROM_CMD_CONFIG);
	write_nic_byte(dev,TX_DMA_POLLING,priv->dma_poll_mask);
	rtl8192_set_mode(dev,EPROM_CMD_NORMAL);
	#endif
}