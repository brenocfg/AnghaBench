#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_1__ linux_stats; int /*<<< orphan*/  ethconv; TYPE_4__* netdev; int /*<<< orphan*/  nsd_rxq; } ;
typedef  TYPE_2__ wlandevice_t ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; TYPE_4__* dev; scalar_t__ data; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_9__ {int* a1; int /*<<< orphan*/  fc; } ;
typedef  TYPE_3__ p80211_hdr_a3_t ;
struct TYPE_10__ {scalar_t__ type; int flags; void* last_rx; int /*<<< orphan*/  dev_addr; } ;
typedef  TYPE_4__ netdevice_t ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_80211_RAW ; 
 int IFF_ALLMULTI ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 scalar_t__ WLAN_DEVICE_OPEN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 scalar_t__ p80211_rx_typedrop (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_p80211_to_ether (TYPE_2__*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void p80211netdev_rx_bh(unsigned long arg)
{
	wlandevice_t *wlandev = (wlandevice_t *) arg;
	struct sk_buff *skb = NULL;
	netdevice_t *dev = wlandev->netdev;
	p80211_hdr_a3_t *hdr;
	u16 fc;

	/* Let's empty our our queue */
	while ((skb = skb_dequeue(&wlandev->nsd_rxq))) {
		if (wlandev->state == WLAN_DEVICE_OPEN) {

			if (dev->type != ARPHRD_ETHER) {
				/* RAW frame; we shouldn't convert it */
				/* XXX Append the Prism Header here instead. */

				/* set up various data fields */
				skb->dev = dev;
				skb_reset_mac_header(skb);
				skb->ip_summed = CHECKSUM_NONE;
				skb->pkt_type = PACKET_OTHERHOST;
				skb->protocol = htons(ETH_P_80211_RAW);
				dev->last_rx = jiffies;

				wlandev->linux_stats.rx_packets++;
				wlandev->linux_stats.rx_bytes += skb->len;
				netif_rx_ni(skb);
				continue;
			} else {
				hdr = (p80211_hdr_a3_t *) skb->data;
				fc = le16_to_cpu(hdr->fc);
				if (p80211_rx_typedrop(wlandev, fc)) {
					dev_kfree_skb(skb);
					continue;
				}

				/* perform mcast filtering */
				if (wlandev->netdev->flags & IFF_ALLMULTI) {
					/* allow my local address through */
					if (memcmp
					    (hdr->a1, wlandev->netdev->dev_addr,
					     ETH_ALEN) != 0) {
						/* but reject anything else that isn't multicast */
						if (!(hdr->a1[0] & 0x01)) {
							dev_kfree_skb(skb);
							continue;
						}
					}
				}

				if (skb_p80211_to_ether
				    (wlandev, wlandev->ethconv, skb) == 0) {
					skb->dev->last_rx = jiffies;
					wlandev->linux_stats.rx_packets++;
					wlandev->linux_stats.rx_bytes +=
					    skb->len;
					netif_rx_ni(skb);
					continue;
				}
				pr_debug("p80211_to_ether failed.\n");
			}
		}
		dev_kfree_skb(skb);
	}
}