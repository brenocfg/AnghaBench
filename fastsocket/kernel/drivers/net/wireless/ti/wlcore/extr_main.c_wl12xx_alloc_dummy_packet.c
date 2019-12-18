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
struct wl1271_tx_hw_descr {int dummy; } ;
struct wl1271 {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct ieee80211_tx_info {int dummy; } ;
struct ieee80211_hdr_3addr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int IEEE80211_FCTL_TODS ; 
 int IEEE80211_FTYPE_DATA ; 
 struct ieee80211_hdr_3addr* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_STYPE_NULLFUNC ; 
 int TOTAL_TX_DUMMY_PACKET_SIZE ; 
 int /*<<< orphan*/  WL1271_TID_MGMT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_hdr_3addr*,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_hdr_3addr* skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

__attribute__((used)) static struct sk_buff *wl12xx_alloc_dummy_packet(struct wl1271 *wl)
{
	struct sk_buff *skb;
	struct ieee80211_hdr_3addr *hdr;
	unsigned int dummy_packet_size;

	dummy_packet_size = TOTAL_TX_DUMMY_PACKET_SIZE -
			    sizeof(struct wl1271_tx_hw_descr) - sizeof(*hdr);

	skb = dev_alloc_skb(TOTAL_TX_DUMMY_PACKET_SIZE);
	if (!skb) {
		wl1271_warning("Failed to allocate a dummy packet skb");
		return NULL;
	}

	skb_reserve(skb, sizeof(struct wl1271_tx_hw_descr));

	hdr = (struct ieee80211_hdr_3addr *) skb_put(skb, sizeof(*hdr));
	memset(hdr, 0, sizeof(*hdr));
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					 IEEE80211_STYPE_NULLFUNC |
					 IEEE80211_FCTL_TODS);

	memset(skb_put(skb, dummy_packet_size), 0, dummy_packet_size);

	/* Dummy packets require the TID to be management */
	skb->priority = WL1271_TID_MGMT;

	/* Initialize all fields that might be used */
	skb_set_queue_mapping(skb, 0);
	memset(IEEE80211_SKB_CB(skb), 0, sizeof(struct ieee80211_tx_info));

	return skb;
}