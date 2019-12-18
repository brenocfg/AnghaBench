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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ cb; } ;
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_4__ {scalar_t__ queue_index; int RATRIndex; int bTxDisableRateFallBack; int bTxUseDriverAssingedRate; int bTxEnableFwCalcDur; } ;
typedef  TYPE_2__ cb_desc ;
struct TYPE_3__ {int /*<<< orphan*/  tx_headroom; } ;

/* Variables and functions */
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 scalar_t__ TXCMD_QUEUE ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct net_device**,int) ; 
 int rtl8192_tx (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  rtl819xE_tx_cmd (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8192_hard_start_xmit(struct sk_buff *skb,struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);


	int ret;
	//unsigned long flags;
        cb_desc *tcb_desc = (cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
        u8 queue_index = tcb_desc->queue_index;


	//spin_lock_irqsave(&priv->tx_lock,flags);

        memcpy((unsigned char *)(skb->cb),&dev,sizeof(dev));
	if(queue_index == TXCMD_QUEUE) {
	//	skb_push(skb, USB_HWDESC_HEADER_LEN);
		rtl819xE_tx_cmd(dev, skb);
		ret = 0;
	        //spin_unlock_irqrestore(&priv->tx_lock,flags);
		return ret;
	} else {
	//	RT_TRACE(COMP_SEND, "To send management packet\n");
		tcb_desc->RATRIndex = 7;
		tcb_desc->bTxDisableRateFallBack = 1;
		tcb_desc->bTxUseDriverAssingedRate = 1;
		tcb_desc->bTxEnableFwCalcDur = 1;
		skb_push(skb, priv->ieee80211->tx_headroom);
		ret = rtl8192_tx(dev, skb);
		if(ret != 0) {
			kfree_skb(skb);
		};
	}

//	priv->ieee80211->stats.tx_bytes+=skb->len;
//	priv->ieee80211->stats.tx_packets++;

	//spin_unlock_irqrestore(&priv->tx_lock,flags);

	return ret;

}