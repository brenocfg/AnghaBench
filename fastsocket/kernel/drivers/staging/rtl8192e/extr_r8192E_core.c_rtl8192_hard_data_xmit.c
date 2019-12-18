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
struct sk_buff {scalar_t__ len; scalar_t__ cb; } ;
struct r8192_priv {TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_6__ {scalar_t__ queue_index; int RATRIndex; int bTxDisableRateFallBack; int bTxUseDriverAssingedRate; int bTxEnableFwCalcDur; } ;
typedef  TYPE_3__ cb_desc ;
struct TYPE_4__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct TYPE_5__ {TYPE_1__ stats; scalar_t__ tx_headroom; } ;

/* Variables and functions */
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 scalar_t__ MGNT_QUEUE ; 
 scalar_t__ TXCMD_QUEUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct net_device**,int) ; 
 int rtl8192_tx (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void rtl8192_hard_data_xmit(struct sk_buff *skb, struct net_device *dev, int rate)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	int ret;
	//unsigned long flags;
	cb_desc *tcb_desc = (cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u8 queue_index = tcb_desc->queue_index;
	/* shall not be referred by command packet */
	assert(queue_index != TXCMD_QUEUE);

	//spin_lock_irqsave(&priv->tx_lock,flags);

        memcpy((unsigned char *)(skb->cb),&dev,sizeof(dev));
#if 0
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	tcb_desc->bTxEnableFwCalcDur = 1;
#endif
	skb_push(skb, priv->ieee80211->tx_headroom);
	ret = rtl8192_tx(dev, skb);
	if(ret != 0) {
		kfree_skb(skb);
	};

//
	if(queue_index!=MGNT_QUEUE) {
	priv->ieee80211->stats.tx_bytes+=(skb->len - priv->ieee80211->tx_headroom);
	priv->ieee80211->stats.tx_packets++;
	}

	//spin_unlock_irqrestore(&priv->tx_lock,flags);

//	return ret;
	return;
}