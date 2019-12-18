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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {struct net_device* dev; scalar_t__ cb; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct hostap_skb_tx_data {int /*<<< orphan*/  iface; int /*<<< orphan*/  magic; scalar_t__ bssid; scalar_t__ sa; scalar_t__ da; int /*<<< orphan*/  frame_control; } ;
struct hostap_ieee80211_mgmt {int /*<<< orphan*/  iface; int /*<<< orphan*/  magic; scalar_t__ bssid; scalar_t__ sa; scalar_t__ da; int /*<<< orphan*/  frame_control; } ;
struct TYPE_3__ {struct net_device* dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int ENOMEM ; 
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  HOSTAP_SKB_TX_DATA_MAGIC ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_MGMT_HDR_LEN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (struct hostap_skb_tx_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 scalar_t__ skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

int prism2_sta_send_mgmt(local_info_t *local, u8 *dst, u16 stype,
			 u8 *body, size_t bodylen)
{
	struct sk_buff *skb;
	struct hostap_ieee80211_mgmt *mgmt;
	struct hostap_skb_tx_data *meta;
	struct net_device *dev = local->dev;

	skb = dev_alloc_skb(IEEE80211_MGMT_HDR_LEN + bodylen);
	if (skb == NULL)
		return -ENOMEM;

	mgmt = (struct hostap_ieee80211_mgmt *)
		skb_put(skb, IEEE80211_MGMT_HDR_LEN);
	memset(mgmt, 0, IEEE80211_MGMT_HDR_LEN);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT | stype);
	memcpy(mgmt->da, dst, ETH_ALEN);
	memcpy(mgmt->sa, dev->dev_addr, ETH_ALEN);
	memcpy(mgmt->bssid, dst, ETH_ALEN);
	if (body)
		memcpy(skb_put(skb, bodylen), body, bodylen);

	meta = (struct hostap_skb_tx_data *) skb->cb;
	memset(meta, 0, sizeof(*meta));
	meta->magic = HOSTAP_SKB_TX_DATA_MAGIC;
	meta->iface = netdev_priv(dev);

	skb->dev = dev;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	dev_queue_xmit(skb);

	return 0;
}