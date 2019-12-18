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
struct sk_buff {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int IEEE80211_QOS_CTL_A_MSDU_PRESENT ; 
 int NET_IP_ALIGN ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_has_a4 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *carl9170_rx_copy_data(u8 *buf, int len)
{
	struct sk_buff *skb;
	int reserved = 0;
	struct ieee80211_hdr *hdr = (void *) buf;

	if (ieee80211_is_data_qos(hdr->frame_control)) {
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		reserved += NET_IP_ALIGN;

		if (*qc & IEEE80211_QOS_CTL_A_MSDU_PRESENT)
			reserved += NET_IP_ALIGN;
	}

	if (ieee80211_has_a4(hdr->frame_control))
		reserved += NET_IP_ALIGN;

	reserved = 32 + (reserved & NET_IP_ALIGN);

	skb = dev_alloc_skb(len + reserved);
	if (likely(skb)) {
		skb_reserve(skb, reserved);
		memcpy(skb_put(skb, len), buf, len);
	}

	return skb;
}