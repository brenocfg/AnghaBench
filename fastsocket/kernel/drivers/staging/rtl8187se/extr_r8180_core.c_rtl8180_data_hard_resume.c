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
struct r8180_priv {int /*<<< orphan*/  dma_poll_stop_mask; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  EPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  TPPOLLSTOP_AC_VIQ ; 
 int /*<<< orphan*/  TPPollStop ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8180_set_mode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8180_data_hard_resume(struct net_device *dev)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	rtl8180_set_mode(dev,EPROM_CMD_CONFIG);
	priv->dma_poll_stop_mask &= ~(TPPOLLSTOP_AC_VIQ);
	write_nic_byte(dev,TPPollStop, priv->dma_poll_stop_mask);
	rtl8180_set_mode(dev,EPROM_CMD_NORMAL);
}