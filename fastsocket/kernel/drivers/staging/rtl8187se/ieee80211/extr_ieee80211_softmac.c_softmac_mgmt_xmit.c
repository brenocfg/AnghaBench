#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_hdr_3addr {void* seq_ctl; } ;
struct ieee80211_device {short softmac_features; int* seq_ctrl; int /*<<< orphan*/  mgmt_tx_lock; TYPE_1__* dev; int /*<<< orphan*/  (* softmac_hard_start_xmit ) (struct sk_buff*,TYPE_1__*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  basic_rate; int /*<<< orphan*/  (* softmac_data_hard_start_xmit ) (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ queue_stop; } ;
struct TYPE_3__ {void* trans_start; } ;

/* Variables and functions */
 short IEEE_SOFTMAC_SINGLE_QUEUE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  enqueue_mgmt (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_sta_wakeup (struct ieee80211_device*,int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*,TYPE_1__*) ; 

inline void softmac_mgmt_xmit(struct sk_buff *skb, struct ieee80211_device *ieee)
{
	unsigned long flags;
	short single = ieee->softmac_features & IEEE_SOFTMAC_SINGLE_QUEUE;
	struct ieee80211_hdr_3addr  *header=
		(struct ieee80211_hdr_3addr  *) skb->data;


	spin_lock_irqsave(&ieee->lock, flags);

	/* called with 2nd param 0, no mgmt lock required */
	ieee80211_sta_wakeup(ieee,0);

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
			ieee->dev->trans_start = jiffies;
			ieee->softmac_data_hard_start_xmit(skb,ieee->dev,ieee->basic_rate);
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

		/* avoid watchdog triggers */
		ieee->dev->trans_start = jiffies;
		ieee->softmac_hard_start_xmit(skb,ieee->dev);

		spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags);
	}
}