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
struct ieee80211_device {short softmac_features; int* seq_ctrl; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* softmac_hard_start_xmit ) (struct sk_buff*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  basic_rate; int /*<<< orphan*/  (* softmac_data_hard_start_xmit ) (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int RATRIndex; int bTxDisableRateFallBack; int bTxUseDriverAssingedRate; int /*<<< orphan*/  data_rate; int /*<<< orphan*/  queue_index; } ;
typedef  TYPE_1__ cb_desc ;

/* Variables and functions */
 short IEEE_SOFTMAC_SINGLE_QUEUE ; 
 int /*<<< orphan*/  MGNT_QUEUE ; 
 int /*<<< orphan*/  MgntQuery_MgntFrameTxRate (struct ieee80211_device*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*,int /*<<< orphan*/ ) ; 

inline void softmac_ps_mgmt_xmit(struct sk_buff *skb, struct ieee80211_device *ieee)
{

	short single = ieee->softmac_features & IEEE_SOFTMAC_SINGLE_QUEUE;
	struct ieee80211_hdr_3addr  *header =
		(struct ieee80211_hdr_3addr  *) skb->data;
        cb_desc *tcb_desc = (cb_desc *)(skb->cb + 8);

	tcb_desc->queue_index = MGNT_QUEUE;
	tcb_desc->data_rate = MgntQuery_MgntFrameTxRate(ieee);
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	//printk("=============>%s()\n", __FUNCTION__);
	if(single){

		header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

		if (ieee->seq_ctrl[0] == 0xFFF)
			ieee->seq_ctrl[0] = 0;
		else
			ieee->seq_ctrl[0]++;

		/* avoid watchdog triggers */
	//	ieee->dev->trans_start = jiffies;
		ieee->softmac_data_hard_start_xmit(skb,ieee->dev,ieee->basic_rate);

	}else{

		header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

		if (ieee->seq_ctrl[0] == 0xFFF)
			ieee->seq_ctrl[0] = 0;
		else
			ieee->seq_ctrl[0]++;

		ieee->softmac_hard_start_xmit(skb,ieee->dev);

	}
	//dev_kfree_skb_any(skb);//edit by thomas
}