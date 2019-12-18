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
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int IEEE80211_FCTL_STYPE ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
#define  IEEE80211_STYPE_ACTION 131 
#define  IEEE80211_STYPE_BEACON 130 
#define  IEEE80211_STYPE_PROBE_REQ 129 
#define  IEEE80211_STYPE_PROBE_RESP 128 
 int /*<<< orphan*/  ieee80211_mesh_rx_bcn_presp (struct ieee80211_sub_if_data*,int,struct ieee80211_mgmt*,int /*<<< orphan*/ ,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  ieee80211_mesh_rx_mgmt_action (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,int /*<<< orphan*/ ,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  ieee80211_mesh_rx_probe_req (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

void ieee80211_mesh_rx_queued_mgmt(struct ieee80211_sub_if_data *sdata,
				   struct sk_buff *skb)
{
	struct ieee80211_rx_status *rx_status;
	struct ieee80211_mgmt *mgmt;
	u16 stype;

	rx_status = IEEE80211_SKB_RXCB(skb);
	mgmt = (struct ieee80211_mgmt *) skb->data;
	stype = le16_to_cpu(mgmt->frame_control) & IEEE80211_FCTL_STYPE;

	switch (stype) {
	case IEEE80211_STYPE_PROBE_RESP:
	case IEEE80211_STYPE_BEACON:
		ieee80211_mesh_rx_bcn_presp(sdata, stype, mgmt, skb->len,
					    rx_status);
		break;
	case IEEE80211_STYPE_PROBE_REQ:
		ieee80211_mesh_rx_probe_req(sdata, mgmt, skb->len);
		break;
	case IEEE80211_STYPE_ACTION:
		ieee80211_mesh_rx_mgmt_action(sdata, mgmt, skb->len, rx_status);
		break;
	}
}