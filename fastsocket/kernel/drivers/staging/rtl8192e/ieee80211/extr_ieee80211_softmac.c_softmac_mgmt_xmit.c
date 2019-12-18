#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ cb; scalar_t__ data; } ;
struct ieee80211_hdr_3addr {void* seq_ctl; } ;
struct ieee80211_device {short softmac_features; int* seq_ctrl; int /*<<< orphan*/  mgmt_tx_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* softmac_hard_start_xmit ) (struct sk_buff*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * skb_waitQ; scalar_t__ queue_stop; int /*<<< orphan*/  (* check_nic_enough_desc ) (int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  basic_rate; int /*<<< orphan*/  (* softmac_data_hard_start_xmit ) (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {size_t queue_index; int RATRIndex; int bTxDisableRateFallBack; int bTxUseDriverAssingedRate; int /*<<< orphan*/  data_rate; } ;
typedef  TYPE_1__ cb_desc ;

/* Variables and functions */
 short IEEE_SOFTMAC_SINGLE_QUEUE ; 
 size_t MGNT_QUEUE ; 
 int /*<<< orphan*/  MgntQuery_MgntFrameTxRate (struct ieee80211_device*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  enqueue_mgmt (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_sta_wakeup (struct ieee80211_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub3 (struct sk_buff*,int /*<<< orphan*/ ) ; 

inline void softmac_mgmt_xmit(struct sk_buff *skb, struct ieee80211_device *ieee)
{
	unsigned long flags;
	short single = ieee->softmac_features & IEEE_SOFTMAC_SINGLE_QUEUE;
	struct ieee80211_hdr_3addr  *header=
		(struct ieee80211_hdr_3addr  *) skb->data;

	cb_desc *tcb_desc = (cb_desc *)(skb->cb + 8);
	spin_lock_irqsave(&ieee->lock, flags);

	/* called with 2nd param 0, no mgmt lock required */
	ieee80211_sta_wakeup(ieee,0);

	tcb_desc->queue_index = MGNT_QUEUE;
	tcb_desc->data_rate = MgntQuery_MgntFrameTxRate(ieee);
        tcb_desc->RATRIndex = 7;
        tcb_desc->bTxDisableRateFallBack = 1;
        tcb_desc->bTxUseDriverAssingedRate = 1;

	if(single){
		if(ieee->queue_stop){
			enqueue_mgmt(ieee,skb);
		}else{
			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0]<<4);

			if (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			else
				ieee->seq_ctrl[0]++;

			/* avoid watchdog triggers */
	//		ieee->dev->trans_start = jiffies;
			ieee->softmac_data_hard_start_xmit(skb,ieee->dev,ieee->basic_rate);
			//dev_kfree_skb_any(skb);//edit by thomas
		}

		spin_unlock_irqrestore(&ieee->lock, flags);
	}else{
		spin_unlock_irqrestore(&ieee->lock, flags);
		spin_lock_irqsave(&ieee->mgmt_tx_lock, flags);

		header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

		if (ieee->seq_ctrl[0] == 0xFFF)
			ieee->seq_ctrl[0] = 0;
		else
			ieee->seq_ctrl[0]++;

		/* check wether the managed packet queued greater than 5 */
		if(!ieee->check_nic_enough_desc(ieee->dev,tcb_desc->queue_index)||\
				(skb_queue_len(&ieee->skb_waitQ[tcb_desc->queue_index]) != 0)||\
				(ieee->queue_stop) ) {
			/* insert the skb packet to the management queue */
			/* as for the completion function, it does not need
			 * to check it any more.
			 * */
			//printk("%s():insert to waitqueue!\n",__FUNCTION__);
			skb_queue_tail(&ieee->skb_waitQ[tcb_desc->queue_index], skb);
		} else {
			//printk("TX packet!\n");
			ieee->softmac_hard_start_xmit(skb,ieee->dev);
			//dev_kfree_skb_any(skb);//edit by thomas
		}
		spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags);
	}
}