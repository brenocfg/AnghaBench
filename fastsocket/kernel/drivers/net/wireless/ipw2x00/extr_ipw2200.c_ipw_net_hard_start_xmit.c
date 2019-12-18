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
struct net_device {int dummy; } ;
struct libipw_txb {int /*<<< orphan*/  payload_size; } ;
struct ipw_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  prom_net_dev; } ;
typedef  scalar_t__ netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_TX (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NETDEV_TX_OK ; 
 int /*<<< orphan*/  __ipw_led_activity_on (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_handle_promiscuous_tx (struct ipw_priv*,struct libipw_txb*) ; 
 scalar_t__ ipw_tx_skb (struct ipw_priv*,struct libipw_txb*,int) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ rtap_iface ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t ipw_net_hard_start_xmit(struct libipw_txb *txb,
					   struct net_device *dev, int pri)
{
	struct ipw_priv *priv = libipw_priv(dev);
	unsigned long flags;
	netdev_tx_t ret;

	IPW_DEBUG_TX("dev->xmit(%d bytes)\n", txb->payload_size);
	spin_lock_irqsave(&priv->lock, flags);

#ifdef CONFIG_IPW2200_PROMISCUOUS
	if (rtap_iface && netif_running(priv->prom_net_dev))
		ipw_handle_promiscuous_tx(priv, txb);
#endif

	ret = ipw_tx_skb(priv, txb, pri);
	if (ret == NETDEV_TX_OK)
		__ipw_led_activity_on(priv);
	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;
}