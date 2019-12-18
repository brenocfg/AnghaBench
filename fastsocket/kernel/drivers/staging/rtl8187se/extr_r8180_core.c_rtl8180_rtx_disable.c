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
typedef  int u8 ;
struct r8180_priv {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  rx_skb_complete; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int CMD_RX_ENABLE_SHIFT ; 
 int CMD_TX_ENABLE_SHIFT ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8180_rtx_disable(struct net_device *dev)
{
	u8 cmd;
	struct r8180_priv *priv = ieee80211_priv(dev);

	cmd=read_nic_byte(dev,CMD);
	write_nic_byte(dev, CMD, cmd &~ \
		       ((1<<CMD_RX_ENABLE_SHIFT)|(1<<CMD_TX_ENABLE_SHIFT)));
	force_pci_posting(dev);
	mdelay(10);

	if(!priv->rx_skb_complete)
		dev_kfree_skb_any(priv->rx_skb);
}