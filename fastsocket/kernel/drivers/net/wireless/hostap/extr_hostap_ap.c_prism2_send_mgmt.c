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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {struct net_device* dev; scalar_t__ cb; } ;
struct net_device {int flags; char* dev_addr; int /*<<< orphan*/  name; } ;
struct ieee80211_hdr {int /*<<< orphan*/  tx_cb_idx; struct hostap_interface* iface; int /*<<< orphan*/  magic; int /*<<< orphan*/  frame_control; struct ieee80211_hdr* addr3; struct ieee80211_hdr* addr2; struct ieee80211_hdr* addr1; } ;
struct hostap_skb_tx_data {int /*<<< orphan*/  tx_cb_idx; struct hostap_interface* iface; int /*<<< orphan*/  magic; int /*<<< orphan*/  frame_control; struct hostap_skb_tx_data* addr3; struct hostap_skb_tx_data* addr2; struct hostap_skb_tx_data* addr1; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_2__ {struct net_device* dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_AP ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  HOSTAP_SKB_TX_DATA_MAGIC ; 
 int /*<<< orphan*/  IEEE80211_FCTL_FROMDS ; 
 int IFF_UP ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int hostap_80211_get_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_hdr*,char*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_hdr*,int /*<<< orphan*/ ,int) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 struct ieee80211_hdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static void prism2_send_mgmt(struct net_device *dev,
			     u16 type_subtype, char *body,
			     int body_len, u8 *addr, u16 tx_cb_idx)
{
	struct hostap_interface *iface;
	local_info_t *local;
	struct ieee80211_hdr *hdr;
	u16 fc;
	struct sk_buff *skb;
	struct hostap_skb_tx_data *meta;
	int hdrlen;

	iface = netdev_priv(dev);
	local = iface->local;
	dev = local->dev; /* always use master radio device */
	iface = netdev_priv(dev);

	if (!(dev->flags & IFF_UP)) {
		PDEBUG(DEBUG_AP, "%s: prism2_send_mgmt - device is not UP - "
		       "cannot send frame\n", dev->name);
		return;
	}

	skb = dev_alloc_skb(sizeof(*hdr) + body_len);
	if (skb == NULL) {
		PDEBUG(DEBUG_AP, "%s: prism2_send_mgmt failed to allocate "
		       "skb\n", dev->name);
		return;
	}

	fc = type_subtype;
	hdrlen = hostap_80211_get_hdrlen(cpu_to_le16(type_subtype));
	hdr = (struct ieee80211_hdr *) skb_put(skb, hdrlen);
	if (body)
		memcpy(skb_put(skb, body_len), body, body_len);

	memset(hdr, 0, hdrlen);

	/* FIX: ctrl::ack sending used special HFA384X_TX_CTRL_802_11
	 * tx_control instead of using local->tx_control */


	memcpy(hdr->addr1, addr, ETH_ALEN); /* DA / RA */
	if (ieee80211_is_data(hdr->frame_control)) {
		fc |= IEEE80211_FCTL_FROMDS;
		memcpy(hdr->addr2, dev->dev_addr, ETH_ALEN); /* BSSID */
		memcpy(hdr->addr3, dev->dev_addr, ETH_ALEN); /* SA */
	} else if (ieee80211_is_ctl(hdr->frame_control)) {
		/* control:ACK does not have addr2 or addr3 */
		memset(hdr->addr2, 0, ETH_ALEN);
		memset(hdr->addr3, 0, ETH_ALEN);
	} else {
		memcpy(hdr->addr2, dev->dev_addr, ETH_ALEN); /* SA */
		memcpy(hdr->addr3, dev->dev_addr, ETH_ALEN); /* BSSID */
	}

	hdr->frame_control = cpu_to_le16(fc);

	meta = (struct hostap_skb_tx_data *) skb->cb;
	memset(meta, 0, sizeof(*meta));
	meta->magic = HOSTAP_SKB_TX_DATA_MAGIC;
	meta->iface = iface;
	meta->tx_cb_idx = tx_cb_idx;

	skb->dev = dev;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	dev_queue_xmit(skb);
}