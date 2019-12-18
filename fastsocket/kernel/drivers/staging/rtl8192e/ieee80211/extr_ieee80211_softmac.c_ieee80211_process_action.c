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
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_hdr {int dummy; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int ACT_ADDBAREQ ; 
 int ACT_ADDBARSP ; 
#define  ACT_CAT_BA 128 
 int ACT_DELBA ; 
 int /*<<< orphan*/  IEEE80211_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEEE80211_DL_ERR ; 
 int* ieee80211_get_payload (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_rx_ADDBAReq (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_ADDBARsp (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_DELBA (struct ieee80211_device*,struct sk_buff*) ; 

void ieee80211_process_action(struct ieee80211_device* ieee, struct sk_buff* skb)
{
	struct ieee80211_hdr* header = (struct ieee80211_hdr*)skb->data;
	u8* act = ieee80211_get_payload(header);
	u8 tmp = 0;
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA|IEEE80211_DL_BA, skb->data, skb->len);
	if (act == NULL)
	{
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "error to get payload of action frame\n");
		return;
	}
	tmp = *act;
	act ++;
	switch (tmp)
	{
		case ACT_CAT_BA:
			if (*act == ACT_ADDBAREQ)
			ieee80211_rx_ADDBAReq(ieee, skb);
			else if (*act == ACT_ADDBARSP)
			ieee80211_rx_ADDBARsp(ieee, skb);
			else if (*act == ACT_DELBA)
			ieee80211_rx_DELBA(ieee, skb);
			break;
		default:
//			if (net_ratelimit())
//			IEEE80211_DEBUG(IEEE80211_DL_BA, "unknown action frame(%d)\n", tmp);
			break;
	}
	return;

}