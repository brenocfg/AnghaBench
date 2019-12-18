#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ cb; } ;
struct r8192_priv {TYPE_2__* ieee80211; } ;
struct TYPE_3__ {int data_rate; int RATRIndex; int bTxDisableRateFallBack; int bTxUseDriverAssingedRate; int /*<<< orphan*/  queue_index; } ;
typedef  TYPE_1__ cb_desc ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_headroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_QUEUE ; 
 struct sk_buff* ieee80211_get_beacon (TYPE_2__*) ; 
 int /*<<< orphan*/  rtl8192_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

void rtl8192_prepare_beacon(struct r8192_priv *priv)
{
	struct sk_buff *skb;
	//unsigned long flags;
	cb_desc *tcb_desc;

	skb = ieee80211_get_beacon(priv->ieee80211);
	tcb_desc = (cb_desc *)(skb->cb + 8);
        //printk("===========> %s\n", __FUNCTION__);
	//spin_lock_irqsave(&priv->tx_lock,flags);
	/* prepare misc info for the beacon xmit */
	tcb_desc->queue_index = BEACON_QUEUE;
	/* IBSS does not support HT yet, use 1M defautly */
	tcb_desc->data_rate = 2;
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;

	skb_push(skb, priv->ieee80211->tx_headroom);
	if(skb){
		rtl8192_tx(priv->ieee80211->dev,skb);
	}
	//spin_unlock_irqrestore (&priv->tx_lock, flags);
}