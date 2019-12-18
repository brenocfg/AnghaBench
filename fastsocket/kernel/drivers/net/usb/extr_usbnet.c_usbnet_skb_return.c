#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbnet {TYPE_2__* net; int /*<<< orphan*/  rxq_pause; int /*<<< orphan*/  flags; } ;
struct skb_data {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  cb; int /*<<< orphan*/  protocol; scalar_t__ len; } ;
struct ethhdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_RX_PAUSED ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,TYPE_2__*,char*,int,...) ; 
 int netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void usbnet_skb_return (struct usbnet *dev, struct sk_buff *skb)
{
	int	status;

	if (test_bit(EVENT_RX_PAUSED, &dev->flags)) {
		skb_queue_tail(&dev->rxq_pause, skb);
		return;
	}

	skb->protocol = eth_type_trans (skb, dev->net);
	dev->net->stats.rx_packets++;
	dev->net->stats.rx_bytes += skb->len;

	netif_dbg(dev, rx_status, dev->net, "< rx, len %zu, type 0x%x\n",
		  skb->len + sizeof (struct ethhdr), skb->protocol);
	memset (skb->cb, 0, sizeof (struct skb_data));
	status = netif_rx (skb);
	if (status != NET_RX_SUCCESS)
		netif_dbg(dev, rx_err, dev->net,
			  "netif_rx status %d\n", status);
}