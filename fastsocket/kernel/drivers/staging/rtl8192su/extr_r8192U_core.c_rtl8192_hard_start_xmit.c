#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ cb; } ;
struct r8192_priv {int /*<<< orphan*/  tx_lock; TYPE_2__* ops; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_6__ {scalar_t__ queue_index; } ;
typedef  TYPE_3__ cb_desc ;
struct TYPE_5__ {int (* rtl819x_tx ) (struct net_device*,struct sk_buff*) ;int /*<<< orphan*/  (* rtl819x_tx_cmd ) (struct net_device*,struct sk_buff*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  tx_headroom; } ;

/* Variables and functions */
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 scalar_t__ TXCMD_QUEUE ; 
 int /*<<< orphan*/  USB_HWDESC_HEADER_LEN ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct net_device**,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct sk_buff*) ; 
 int stub2 (struct net_device*,struct sk_buff*) ; 

int rtl8192_hard_start_xmit(struct sk_buff *skb,struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	int ret;
	unsigned long flags;
        cb_desc *tcb_desc = (cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
        u8 queue_index = tcb_desc->queue_index;


	spin_lock_irqsave(&priv->tx_lock,flags);

        memcpy((unsigned char *)(skb->cb),&dev,sizeof(dev));
	if(queue_index == TXCMD_QUEUE) {
		skb_push(skb, USB_HWDESC_HEADER_LEN);
		priv->ops->rtl819x_tx_cmd(dev, skb);
		ret = 1;
	        spin_unlock_irqrestore(&priv->tx_lock,flags);
		return ret;
	} else {
		skb_push(skb, priv->ieee80211->tx_headroom);
		ret = priv->ops->rtl819x_tx(dev, skb);
	}

	spin_unlock_irqrestore(&priv->tx_lock,flags);

	return ret;
}